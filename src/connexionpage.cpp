#include "headers/connexionpage.h"
#include "ui_connexionpage.h"
#include "headers/XMLParser.h"
#include <QXmlStreamReader>

ConnexionPage::ConnexionPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
    ui->input_password->setEchoMode(QLineEdit::Password);
    connect(ui->button_connection, &QPushButton::clicked, this, &ConnexionPage::onConnectionButton_Click);
    connect(ui->button_inscription, &QPushButton::clicked, this, &ConnexionPage::onInscriptionButton_Click);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}

void ConnexionPage::onConnectionButton_Click(){
    QString typedLogin = ui->input_login->text();
    QString typedPassword = ui->input_password->text();
    User foundUser;

    if (XMLParser::CheckConnexion("myFile.xml", foundUser, typedPassword, typedLogin) != 0)
        // TODO : messages d'erreurs en fonction du retour de CheckConnexion (créer une fonction dans XMLParser)
        ui->label_error->setText("Mauvais login et/ou mot de passe");
    else
    {
        MainPage *mpg = new MainPage;
        connect(this, &ConnexionPage::notifyInfoSent, mpg, &MainPage::onInfoSent);
        mpg->show();
        emit notifyInfoSent(foundUser); // On transmet les informations de l'utilisateur à la MainPage
        hide();

    }
}

void ConnexionPage::onInscriptionButton_Click(){
    this->hide();
    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();
}
