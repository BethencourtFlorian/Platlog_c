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
