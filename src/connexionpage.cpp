#include "headers/connexionpage.h"
#include "ui_connexionpage.h"

ConnexionPage::ConnexionPage(QWidget *parent) :
    QDialog(parent),
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
    return 0;
}
