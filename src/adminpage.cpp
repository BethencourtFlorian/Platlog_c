#include "headers/adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &AdminPage::onTreeNode_Clicked);
    connect(ui->tableView, &QTableView::doubleClicked, this, &AdminPage::openFileDialog);
}

AdminPage::~AdminPage()
{
    delete ui;
}

User* AdminPage::getUserWithLogin(QString login){
    for(auto it = listUsers.begin(); it != listUsers.end(); it++)
    {
        if((*it)->getLogin() == login){
            return *it;
        }
    }
    return nullptr;
}

Profile* AdminPage::getProfileWithId(QString id, User* user){
    list<Profile*> listProfiles = user->getProfiles();
    for(auto it = listProfiles.begin(); it != listProfiles.end(); it++)
    {
        if((*it)->getId() == id){
            return *it;
        }
    }
    return nullptr;
}

Database* AdminPage::getDatabaseWithName(QString name, Profile* profile){
    list<Database*> listDatabases = profile->getDatabases();
    for(auto it = listDatabases.begin(); it != listDatabases.end(); it++)
    {
        if((*it)->getName() == name){
            return *it;
        }
    }
    return nullptr;
}

QString convertRight(int right){
    if(right == 1){
        return QString("True");
    }
    if(right == 0){
        return QString("False");
    }
    else
        return QString("");
}

void AdminPage::fillTableWithUser(User *user){
    if(user != nullptr){
        int rows = 1; int columns = 8;
        QStandardItemModel* userModel =  new QStandardItemModel(rows, columns);
        QStringList userLabels = {"Login", "Password", "Email", "FirstName", "LastName", "ReadingRight", "EditRight", "SudoRight"};
        userModel->setHorizontalHeaderLabels(userLabels);

        QStandardItem* login = new QStandardItem(user->getLogin()); login->setTextAlignment(Qt::AlignCenter);
        QStandardItem* password = new QStandardItem(user->getPassword()); password->setTextAlignment(Qt::AlignCenter);
        QStandardItem* email = new QStandardItem(user->getEmail()); email->setTextAlignment(Qt::AlignCenter);
        QStandardItem* firstName = new QStandardItem(user->getFirstName()); firstName->setTextAlignment(Qt::AlignCenter);
        QStandardItem* lastName = new QStandardItem(user->getLastName()); lastName->setTextAlignment(Qt::AlignCenter);
        QStandardItem* readRight = new QStandardItem(convertRight(user->getRightRead())); readRight->setTextAlignment(Qt::AlignCenter);
        QStandardItem* editRight = new QStandardItem(convertRight(user->getRightEdit())); editRight->setTextAlignment(Qt::AlignCenter);
        QStandardItem* sudoRight = new QStandardItem(convertRight(user->getRightSudo())); sudoRight->setTextAlignment(Qt::AlignCenter);
        userModel->appendRow({login, password, email, firstName, lastName, readRight, editRight, sudoRight});

        connect(userModel, &QStandardItemModel::itemChanged, this, &AdminPage::onUserChanged);
        ui->tableView->setModel(userModel);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->setItemDelegateForColumn(5, new ComboBoxDelegate(ui->tableView));
        ui->tableView->setItemDelegateForColumn(6, new ComboBoxDelegate(ui->tableView));
        ui->tableView->setItemDelegateForColumn(7, new ComboBoxDelegate(ui->tableView));
        ui->tableView->resizeColumnsToContents();
        ui->tableView->viewport()->update();
    }
}

void AdminPage::fillTableWithProfile(Profile *profile){
    if(profile != nullptr){
        int rows = 1; int columns = 1;
        QStandardItemModel* profileModel =  new QStandardItemModel(rows, columns);
        QStringList profileLabels = {"Id"};
        profileModel->setHorizontalHeaderLabels(profileLabels);

        QStandardItem* id = new QStandardItem(profile->getId()); id->setTextAlignment(Qt::AlignCenter);
        profileModel->appendRow(id);

        connect(profileModel, &QStandardItemModel::itemChanged, this, &AdminPage::onProfileChanged);
        ui->tableView->setModel(profileModel);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->viewport()->update();
    }
}

void AdminPage::fillTableWithDatabase(Database *database){
    if(database != nullptr){
        int rows = 1; int columns = 2;
        QStandardItemModel* databaseModel =  new QStandardItemModel(rows, columns);
        QStringList databaseLabels = {"Name", "Path"};
        databaseModel->setHorizontalHeaderLabels(databaseLabels);

        QStandardItem* name = new QStandardItem(database->getName()); name->setTextAlignment(Qt::AlignCenter);
        QStandardItem* path = new QStandardItem(database->getPath()); path->setTextAlignment(Qt::AlignCenter);

        databaseModel->appendRow({name, path});

        connect(databaseModel, &QStandardItemModel::itemChanged, this, &AdminPage::onDatabaseChanged);
        ui->tableView->setModel(databaseModel);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->viewport()->update();
    }
}
void AdminPage::onTreeNode_Clicked(QTreeWidgetItem *item, int column){
    // Si on clique sur un user
    if(item->parent() == nullptr){
        User* userClicked = getUserWithLogin(item->text(column));
        fillTableWithUser(userClicked);
    }
    // Si on clique sur un profil
    else if(item->parent()->parent() == nullptr){
        Profile* profileClicked = getProfileWithId(item->text(column), getUserWithLogin(item->parent()->text(column)));
        fillTableWithProfile(profileClicked);
    }
    // Si on clique sur une base de données
    else{
        Database* databaseClicked = getDatabaseWithName(item->text(column), getProfileWithId(item->parent()->text(column), getUserWithLogin(item->parent()->parent()->text(column))));
        fillTableWithDatabase(databaseClicked);
    }
}

void AdminPage::onUserChanged(QStandardItem *item){
    QTreeWidgetItem* userNode = (ui->treeWidget->selectedItems().back());
    User* user = getUserWithLogin(userNode->text(0));
    switch(item->column()){
        case 0 :
            user->setLogin(item->text());
            userNode->setText(0, item->text());
            break;
        case 1 :
            user->setPassword(item->text());
            break;
        case 2 :
            user->setEmail(item->text());
            break;
        case 3 :
            user->setFirstName(item->text());
            break;
        case 4 :
            user->setLastName(item->text());
            break;
        case 5 :
            if(item->text() == "True")
                user->setRightRead(1);
            else
                user->setRightRead(0);
            break;
        case 6 :
            if(item->text() == "True")
                user->setRightEdit(1);
            else
                user->setRightEdit(0);
            break;
        case 7 :
            if(item->text() == "True")
                user->setRightSudo(1);
            else
                user->setRightSudo(0);
            break;
    }
    ui->tableView->resizeColumnsToContents();
}

void AdminPage::onProfileChanged(QStandardItem *item){
    QTreeWidgetItem* profileNode = (ui->treeWidget->selectedItems().back());
    User* user = getUserWithLogin(profileNode->parent()->text(0));
    Profile* profile = getProfileWithId(profileNode->text(0), user);
    profile->setId(item->text());
    profileNode->setText(0, item->text());
    ui->tableView->resizeColumnsToContents();
}

void AdminPage::onDatabaseChanged(QStandardItem *item){
    QTreeWidgetItem* databaseNode = (ui->treeWidget->selectedItems().back());
    User* user = getUserWithLogin(databaseNode->parent()->parent()->text(0));
    Profile* profile = getProfileWithId(databaseNode->parent()->text(0), user);
    Database* database = getDatabaseWithName(databaseNode->text(0), profile);
    switch(item->column()){
        case 0 :
            database->setName(item->text());
            databaseNode->setText(0, item->text());
            break;
        case 1 :
            database->setPath(item->text());
            break;
    }
    ui->tableView->resizeColumnsToContents();
}

void AdminPage::openFileDialog(const QModelIndex& index){
    QTreeWidgetItem* databaseNode = (ui->treeWidget->selectedItems().back());
    if(databaseNode->parent() != nullptr){
        if(databaseNode->parent()->parent() != nullptr && index.column() == 1){
            QString path = QFileDialog::getOpenFileName(this, tr("Open Database"), index.data().toString(), tr("Data Base Files (*.db)"));
            User* user = getUserWithLogin(databaseNode->parent()->parent()->text(0));
            Profile* profile = getProfileWithId(databaseNode->parent()->text(0), user);
            Database* database = getDatabaseWithName(databaseNode->text(0), profile);
            database->setPath(path);
            fillTableWithDatabase(database);
        }
    }
}

void AdminPage::onInfoSent(User& sentUser)
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

void AdminPage::on_button_deconnect_clicked()
{
    this->hide();
    ConnexionPage* connexionPage = new ConnexionPage();
    connexionPage->show();
}

void AdminPage::on_createUserButton_clicked()
{
    qDebug() << "profil créé";
}

void AdminPage::instanciatePage()
{
    listUsers = XMLParser::GetUsers("myFile.xml");

    for(auto it = listUsers.begin(); it != listUsers.end(); it++)
    {
        QLabel* newLabel = new QLabel((*it)->getLogin());

        QTreeWidgetItem* userNode = new QTreeWidgetItem(ui->treeWidget);
        userNode->setText(0, newLabel->text());

        list<Profile*> listProfiles = (*it)->getProfiles();
        for(auto itp = listProfiles.begin(); itp != listProfiles.end(); itp++)
        {
            QLabel* newLabelP = new QLabel((*itp)->getId());

            QTreeWidgetItem* profileNode = new QTreeWidgetItem();
            profileNode->setText(0, newLabelP->text());

            list<Database*> listDatabases = (*itp)->getDatabases();
            for(auto itd = listDatabases.begin(); itd != listDatabases.end(); itd++)
            {
                QLabel* newLabelD = new QLabel((*itd)->getName());

                QTreeWidgetItem* databaseNode = new QTreeWidgetItem();
                databaseNode->setText(0, newLabelD->text());
                profileNode->addChild(databaseNode);
            }
            userNode->addChild(profileNode);
        }
    }
}

void AdminPage::refreshPage()
{

}
