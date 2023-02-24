#include "headers/connexionpage.h"
#include "ui_connexionpage.h"
#include "headers/XMLParser.h"
#include <QXmlStreamReader>

ConnexionPage::ConnexionPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
    connect(ui->button_connection, &QPushButton::clicked, this, &ConnexionPage::onClick);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}

int ConnexionPage::onClick(){
    QString typedLogin = ui->input_login->text();
    QString typedPassword = ui->input_password->text();
    user foundUser;

    /*
     * On fait appel à une fonction du Parser XML qui va parcourir le fichier des utilisateurs
     * et tenter de trouver la combinaison login/mdp rentrée dans le formulaire
    */
    if (XMLParser::CheckConnexion("myFile.xml", foundUser, typedPassword, typedLogin) != 0)
        ui->label_error->setText("Login failed");
    else
    {
        // Si la combinaison existe, on affiche la page d'accueil de l'utilisateur et on cache la page de connexion
        MainPage *mpg = new MainPage;
        connect(this, &ConnexionPage::notifyInfoSent, mpg, &MainPage::onInfoSent);
        mpg->show();
        /*
         * On envoie un signal avec les infos utilisateur à la mainpage,
         * qui pourra les traiter avec la fonction onInfoSent()
        */
        emit notifyInfoSent(foundUser);
        hide();

    }
    return 0;
}
