#include "headers/adminpage.h"
#include "ui_adminpage.h"

AdminPage::AdminPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");
}

AdminPage::~AdminPage()
{
    delete ui;
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
    list<User*> listUsers = XMLParser::GetUsers("myFile.xml");

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
