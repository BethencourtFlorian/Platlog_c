#include "headers/adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");
    connect(ui->treeWidget, &QTreeWidget::itemClicked, this, &AdminPage::onTreeNode_Clicked);
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

void AdminPage::onTreeNode_Clicked(QTreeWidgetItem *item, int column){
    if(item->parent() == nullptr){
        User* userClicked = getUserWithLogin(item->text(column));
        if(userClicked != nullptr){
            qDebug() << "not null";
            int rows = 8; int columns = 1;
            QStandardItemModel* userModel =  new QStandardItemModel(rows, columns);
            QStringList userLabels = {"Login", "Password", "Email", "FirstName", "LastName", "ReadingRight", "EditRight", "SudoRight"};
            userModel->setVerticalHeaderLabels(userLabels);

            userModel->setItem(0, new QStandardItem(userClicked->getLogin()));
            userModel->setItem(1, new QStandardItem(userClicked->getPassword()));
            userModel->setItem(2, new QStandardItem(userClicked->getEmail()));
            userModel->setItem(3, new QStandardItem(userClicked->getFirstName()));
            userModel->setItem(4, new QStandardItem(userClicked->getLastName()));
            userModel->setItem(5, new QStandardItem(convertRight(userClicked->getRightRead())));
            userModel->setItem(6, new QStandardItem(convertRight(userClicked->getRightEdit())));
            userModel->setItem(7, new QStandardItem(convertRight(userClicked->getRightSudo())));

            ui->tableView->setModel(userModel);
            ui->tableView->horizontalHeader()->hide();
            ui->tableView->setItemDelegateForRow(5, new ComboBoxDelegate(ui->tableView));
            ui->tableView->setItemDelegateForRow(6, new ComboBoxDelegate(ui->tableView));
            ui->tableView->setItemDelegateForRow(7, new ComboBoxDelegate(ui->tableView));
            ui->tableView->viewport()->update();
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
