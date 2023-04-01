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
    ui->addProfileButton->setDisabled(true);
    ui->addDatabaseButton->setDisabled(true);
    ui->deleteButton->hide();
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
        int rows = 0; int columns = 8;
        QStandardItemModel* userModel =  new QStandardItemModel(rows, columns);
        QStringList userLabels = {"Login", "Password", "Email", "FirstName", "LastName", "Reading", "Edit", "Sudo"};
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
        int rows = 0; int columns = 1;
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
        int rows = 0; int columns = 2;
        QStandardItemModel* databaseModel =  new QStandardItemModel(rows, columns);
        QStringList databaseLabels = {"Name", "Path"};
        databaseModel->setHorizontalHeaderLabels(databaseLabels);

        QStandardItem* name = new QStandardItem(database->getName()); name->setTextAlignment(Qt::AlignCenter);
        QStandardItem* path = new QStandardItem(database->getPath()); path->setTextAlignment(Qt::AlignCenter);

        databaseModel->appendRow({name, path});

        connect(databaseModel, &QStandardItemModel::itemChanged,this, &AdminPage::onDatabaseChanged);
        ui->tableView->setModel(databaseModel);
        ui->tableView->verticalHeader()->hide();
        ui->tableView->resizeColumnsToContents();
        ui->tableView->viewport()->update();
    }
}

void AdminPage::onTreeNode_Clicked(QTreeWidgetItem *item, int column){
    User* userClicked;
    Profile* profileClicked;
    Database* databaseClicked;

    // Si on clique sur un user
    if(item->parent() == nullptr){
        userClicked = getUserWithLogin(item->text(column));
        fillTableWithUser(userClicked);
        ui->addProfileButton->setDisabled(false);
        ui->addDatabaseButton->setDisabled(true);
        ui->deleteButton->setText("Delete user " + userClicked->getLogin());
    }
    // Si on clique sur un profil
    else if(item->parent()->parent() == nullptr){
        profileClicked = getProfileWithId(item->text(column), getUserWithLogin(item->parent()->text(column)));
        fillTableWithProfile(profileClicked);
        ui->addDatabaseButton->setDisabled(false);
        ui->deleteButton->setText("Delete profile " + profileClicked->getId());
    }
    // Si on clique sur une base de données
    else{
        databaseClicked = getDatabaseWithName(item->text(column), getProfileWithId(item->parent()->text(column), getUserWithLogin(item->parent()->parent()->text(column))));
        fillTableWithDatabase(databaseClicked);
        ui->addDatabaseButton->setDisabled(false);
        ui->deleteButton->setText("Delete database " + databaseClicked->getName());
    }
    ui->deleteButton->resize(ui->deleteButton->sizeHint().width()+10, ui->deleteButton->height());
    ui->deleteButton->show();
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
    MainWindow* mainWindow = new MainWindow(0);
    connect(mainWindow, &MainWindow::notifyCloseSignup, this, &AdminPage::addUserTree);
    mainWindow->show();
}

void AdminPage::on_addProfileButton_clicked()
{
    Profile* profile = new Profile(this, 0);
    connect(profile, &Profile::sendNewId, this, &AdminPage::addProfileTree);
    profile->show();
}

void AdminPage::on_saveButton_clicked(){
    QString filePath("myFile.xml");
    XMLParser::saveChanges(filePath, listUsers);

    QMessageBox msgBox;
    msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
    msgBox.setText("Vos modifications ont bien été enregistrées.");
    msgBox.exec();
}

void AdminPage::on_deleteButton_clicked(){
    QTreeWidgetItem* node = (ui->treeWidget->selectedItems().back());

    User* userClicked = new User();
    Profile* profileClicked = new Profile();
    Database* databaseClicked = new Database();

    QMessageBox msgBox;
    QPushButton *confirm = msgBox.addButton(tr("Confirmer"), QMessageBox::ActionRole);
    QPushButton *cancel = msgBox.addButton(QMessageBox::Abort);

    if(node->parent() == nullptr){
        userClicked = getUserWithLogin(node->text(0));
        msgBox.setText("Etes vous sûr de vouloir supprimer cet utilisateur ?");
        msgBox.setInformativeText("Tous ses profils et les bases de données associées seront également supprimées.");
    }
    // Si on clique sur un profil
    else if(node->parent()->parent() == nullptr){
        profileClicked =  getProfileWithId(node->text(0), getUserWithLogin(node->parent()->text(0)));
        msgBox.setText("Etes vous sûr de vouloir supprimer ce profil ?");
        msgBox.setInformativeText("Toutes les bases de données associées seront également supprimées.");
    }
    // Si on clique sur une base de données
    else{
        databaseClicked = getDatabaseWithName(node->text(0), getProfileWithId(node->parent()->text(0), getUserWithLogin(node->parent()->parent()->text(0))));
        msgBox.setText("Etes vous sûr de vouloir supprimer cette base de données du profil ?");
        msgBox.setInformativeText("Cela n'impactera pas le fichier présent sur le disque");
    }

    msgBox.exec();

    if(msgBox.clickedButton() == confirm){
        delete node;
        ui->deleteButton->hide();
        ui->tableView->setModel(new QStandardItemModel());
        ui->tableView->viewport()->update();
        // Si on a cliqué sur une bdd
        if(databaseClicked->getName() != ""){
            list<Database*> listDatabases = profileClicked->getDatabases();
            listDatabases.remove(databaseClicked);
        }
        // Si on a cliqué sur un profil
        else if(profileClicked->getId() != ""){
            list<Database*> listDatabases = profileClicked->getDatabases();
            for(long unsigned int i = 0; i < listDatabases.size(); i++){
                listDatabases.pop_back();
            }

            list<Profile*> listProfiles = userClicked->getProfiles();
            listProfiles.remove(profileClicked);
        }
        // Si on a cliqué sur un user
        else{
            list<Profile*> listProfiles = userClicked->getProfiles();
            for(auto it = listProfiles.begin(); it != listProfiles.end(); it++)
            {
                list<Database*> listDatabases = (*it)->getDatabases();
                for(long unsigned int i = 0; i < listDatabases.size(); i++){
                    listDatabases.pop_back();
                }
            }

            for(long unsigned int i = 0; i < listProfiles.size(); i++){
                listProfiles.pop_back();
            }
            listUsers.remove(userClicked);
        }
    }
    else if(msgBox.clickedButton() == cancel){
        msgBox.hide();
    }
}

void AdminPage::addProfileTree(QString id){
    QTreeWidgetItem* userNode = (ui->treeWidget->selectedItems().back());
    // On selectionne forcement un user (on remonte si on clique sur un profil ou une bdd)
    while(userNode->parent() != nullptr){
        userNode = userNode->parent();
    }

    User* user = getUserWithLogin(userNode->text(0));
    Profile* profile = new Profile(id, user->getLogin());
    user->addProfile(profile);

    QLabel* newLabelP = new QLabel(id);
    QTreeWidgetItem* newProfileNode = new QTreeWidgetItem();
    newProfileNode->setText(0, newLabelP->text());
    userNode->addChild(newProfileNode);
}

void AdminPage::addUserTree(User* user){
    listUsers.push_back(user);
    QLabel* newLabel = new QLabel(user->getLogin());
    QTreeWidgetItem* userNode = new QTreeWidgetItem(ui->treeWidget);
    userNode->setText(0, newLabel->text());
}

void AdminPage::on_addDatabaseButton_clicked()
{
    DatabaseAdd* dbAdd = new DatabaseAdd(0);
    connect(dbAdd, &DatabaseAdd::sendNewDatabase, this, &AdminPage::addDatabaseTree);
    dbAdd->show();
}

void AdminPage::addDatabaseTree(Database *database){
    QTreeWidgetItem* profileNode = (ui->treeWidget->selectedItems().back());
    // On selectionne forcement un profil (le bouton est désactivé quand on clique sur un user)
    while(profileNode->parent()->parent() != nullptr){
        profileNode = profileNode->parent();
    }

    User* user = getUserWithLogin(profileNode->parent()->text(0));
    Profile* profile = getProfileWithId(profileNode->text(0), user);
    profile->addDb(database);

    QLabel* dbLabel= new QLabel(database->getName());
    QTreeWidgetItem* dbNode = new QTreeWidgetItem();
    dbNode->setText(0, dbLabel->text());
    profileNode->addChild(dbNode);
}

void AdminPage::instanciatePage()
{
    ui->treeWidget->clear();
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
