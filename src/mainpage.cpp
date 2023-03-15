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


void MainPage::on_button_search_database_clicked()
{
    // TODO : CHange default path
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), "C:/Users/Florian/Downloads/chinook", tr("Data Base Files (*.db)"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);

    Database *dbPage = new Database;
    connect(this, &MainPage::notifyDbSent, dbPage, &Database::onDbSent);
    dbPage->show();
    emit notifyDbSent(db); // On transmet la base de données à la page Database
}


void MainPage::on_pushButton_clicked()
{
    Profile* profilePage = new Profile(this);
    connect(this, &MainPage::notifyUsernameProfile, profilePage, &Profile::onLoginSent);
    connect(profilePage,SIGNAL(destroyed()),this,SLOT(refreshPage()));
    QString username = (ui->info_login->text()).mid(8);
    emit notifyUsernameProfile(username);
    profilePage->show();
}

void MainPage::instanciatePage()
{
    XMLParser::FillUser("myFile.xml", user);
    list<Profile*> listProfiles = user.getProfiles();

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidget->setHeaderHidden(true);

    for(auto it = listProfiles.begin(); it != listProfiles.end(); it++)
    {
        QLabel* newLabel = new QLabel((*it)->getId());

        QTreeWidgetItem* treeNode = new QTreeWidgetItem(ui->treeWidget);
        treeNode->setText(0, newLabel->text());

        list<Database*> listDatabases = (*it)->getDatabases();
        for(auto itd = listDatabases.begin(); itd != listDatabases.end(); itd++)
        {
            QLabel* newLabelD = new QLabel((*itd)->getName());

            QTreeWidgetItem* databaseNode = new QTreeWidgetItem();
            databaseNode->setText(0, newLabelD->text());
            treeNode->addChild(databaseNode);
        }
    }
}

void MainPage::refreshPage()
{
    XMLParser::FillUser("myFile.xml", user);
    list<Profile*> listProfiles = user.getProfiles();

    QLabel* newLabel = new QLabel(listProfiles.back()->getId());

    QTreeWidgetItem* treeNode = new QTreeWidgetItem(ui->treeWidget);
    treeNode->setText(0, newLabel->text());
}


