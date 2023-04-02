#include "headers/mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");

}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::onInfoSent(User& sentUser)
{
    user = sentUser;
    // Chaque champ de la vue est remplie avec les informations de l'utilisateur récupérées par la vue Connexion
    ui->title->setText(user.getFirstName() + "'s " + ui->title->text());
    ui->info_login->setText(ui->info_login->text() + " " + user.getLogin());
    ui->info_firstName->setText(ui->info_firstName->text() + " " + user.getFirstName());
    ui->info_lastName->setText(ui->info_lastName->text() + " " + user.getLastName());
    ui->info_mail->setText(ui->info_mail->text() + " " + user.getEmail());

    instanciatePage();
}

void MainPage::on_button_deconnect_clicked()
{
    this->hide();
    ConnexionPage* connexionPage = new ConnexionPage();
    connexionPage->show();
}

void MainPage::on_pushButton_clicked()
{
    Profile* profilePage = new Profile(this);
    connect(this, &MainPage::notifyUsernameProfile, profilePage, &Profile::onLoginSent);
    connect(profilePage,SIGNAL(destroyedProfile()),this,SLOT(refreshProfile()));
    QString username = (ui->info_login->text()).mid(8);
    emit notifyUsernameProfile(username);
    profilePage->show();
}

void MainPage::instanciatePage()
{
    XMLParser::fillUser("myFile.xml", user);
    list<Profile*> listProfiles = user.getProfiles();

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidget->setHeaderHidden(true);

    for(auto it = listProfiles.begin(); it != listProfiles.end(); it++)
    {
        QLabel* newLabel = new QLabel((*it)->getId());
        QTreeWidgetItem* treeNode = new QTreeWidgetItem(ui->treeWidget);
        treeNode->setText(0, newLabel->text());
        list<Database*> listDatabases = (*it)->getDbs();
        for (auto it2 = listDatabases.begin() ; it2 != listDatabases.end(); it2++)
        {
            QLabel* newLabel = new QLabel((*it2)->getName());
            QTreeWidgetItem* databaseNode = new QTreeWidgetItem(treeNode);
            databaseNode->setText(0, newLabel->text());
        }
    }
}

void MainPage::refreshProfile()
{
    XMLParser::fillUser("myFile.xml", user);
    list<Profile*> listProfiles = user.getProfiles();

    QLabel* newLabel = new QLabel(listProfiles.back()->getId());

    QTreeWidgetItem* treeNode = new QTreeWidgetItem(ui->treeWidget);
    treeNode->setText(0, newLabel->text());
}

void MainPage::refreshDB(unsigned int idProfile)
{
    XMLParser::fillUser("myFile.xml", user);
    list<Database*> listDatabases = user.getProfile(idProfile)->getDbs();
    QLabel* newLabel = new QLabel(listDatabases.back()->getName());
    QTreeWidgetItem* treeNode = ui->treeWidget->findItems(user.getProfile(idProfile)->getId(), Qt::MatchContains,  0)[0];
    QTreeWidgetItem* databaseNode = new QTreeWidgetItem(treeNode);
    databaseNode->setText(0, newLabel->text());

}

void MainPage::on_pushButton_2_clicked()
{
    DatabaseAdd* databaseAddPage = new DatabaseAdd();
    if (ui->treeWidget->selectedItems().empty()){
        connect(this, &MainPage::notifyUser, databaseAddPage, &DatabaseAdd::onUserSent);
        emit notifyUser(user);
    }

    else
    {
       connect(this, &MainPage::notifyUserWithSelected, databaseAddPage, &DatabaseAdd::onUserWithSelectedSent);
       emit notifyUserWithSelected(user, ui->treeWidget->currentItem()->text(0));
    }
    connect(databaseAddPage,&DatabaseAdd::destroyedDB,this,&MainPage::refreshDB);
    databaseAddPage->show();
}


void MainPage::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent())
    {
        Database* db = XMLParser::searchDatabase("myFile.xml", user, item->parent()->text(column), item->text(column));
        QSqlDatabase SQLdb = QSqlDatabase::addDatabase("QSQLITE", "DBCONN");

        SQLdb.setDatabaseName(db->getPath());
        SQLdb.open();

        QSqlQuery query(QSqlDatabase::database("DBCONN"));
        query.prepare("SELECT name FROM sqlite_schema WHERE type ='table' AND name NOT LIKE 'sqlite_%'");
        query.exec();

        QSqlQueryModel * modal = new QSqlTableModel;
        modal->setQuery(std::move(query));
        ui->listTable->setModel(modal);
        ui->listTable->show();

        SQLdb.close();
    }
    QSqlDatabase::removeDatabase("DBCONN");

}

void MainPage::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->parent())
    {
        Database* db = XMLParser::searchDatabase("myFile.xml", user, item->parent()->text(column), item->text(column));
        QSqlDatabase SQLdb = QSqlDatabase::addDatabase("QSQLITE");
        SQLdb.setDatabaseName(db->getPath());
        Database *dbPage = new Database;
        dbPage->setRead(user.getRightRead());
        dbPage->setEdit(user.getRightEdit());
        connect(this, &MainPage::notifyDbSent, dbPage, &Database::onDbSent);
        dbPage->show();
        emit notifyDbSent(SQLdb); // On transmet la base de données à la page Database
    }
}


void MainPage::on_pushButton_3_clicked()
{
    if (!ui->treeWidget->selectedItems().empty()){

        QMessageBox::StandardButton reply;

        if (ui->treeWidget->currentItem()->parent() && !ui->treeWidget->currentItem()->parent()->parent())
        {
            reply = QMessageBox::warning(this, tr("Alerte"),
            "Voulez vous vraiment supprimer la base de données " + ui->treeWidget->currentItem()->text(0) + " ?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                XMLParser::deleteDatabaseById("myFile.xml",
                                              user,
                                              ui->treeWidget->currentItem()->parent()->text(0),
                                              ui->treeWidget->currentItem()->text(0));

                ui->treeWidget->currentItem()->parent()->removeChild(ui->treeWidget->currentItem());

            }

        }
        else if (!ui->treeWidget->currentItem()->parent())
        {
            reply = QMessageBox::warning(this, tr("Alerte"),
            "Voulez vous vraiment supprimer le profil " + ui->treeWidget->currentItem()->text(0) + " ainsi que toutes ses bases de données ?", QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes)
            {
                XMLParser::deleteProfileById("myFile.xml",
                                              user,
                                              ui->treeWidget->currentItem()->text(0));
                if (ui->treeWidget->currentItem()->childCount() != 0)
                {
                    for (int i = 0 ; i < ui->treeWidget->currentItem()->childCount() ; i++)
                    {
                        ui->treeWidget->currentItem()->removeChild(ui->treeWidget->currentItem()->child(i));
                    }
                }

                delete ui->treeWidget->currentItem();
            }
        }
    }
}

