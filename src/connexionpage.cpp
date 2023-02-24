#include "headers/connexionpage.h"
#include "ui_connexionpage.h"
#include "headers/XMLParser.h"
#include <QXmlStreamReader>

ConnexionPage::ConnexionPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
    connect(ui->button_connection, &QPushButton::clicked, this, &ConnexionPage::onConnectionButton_Click);
    connect(ui->button_inscription, &QPushButton::clicked, this, &ConnexionPage::onInscriptionButton_Click);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}

int ConnexionPage::onConnectionButton_Click(){
    QString typedLogin = ui->input_login->text();
    QString typedPassword = ui->input_password->text();
    user foundUser;

    if (XMLParser::CheckConnexion("myFile.xml", foundUser, typedPassword, typedLogin) != 0)
        ui->label_error->setText("Login failed");
    else
    {
        MainPage *mpg = new MainPage;
        connect(this, &ConnexionPage::notifyInfoSent, mpg, &MainPage::onInfoSent);
        mpg->show();
        emit notifyInfoSent(foundUser);
        hide();

    }
    return 0;
}

int ConnexionPage::onInscriptionButton_Click(){
    this->hide();
    MainWindow* mainwindow = new MainWindow();
    mainwindow->show();
    return 0;
}
