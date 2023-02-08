#include "connexionpage.h"
#include "ui_connexionpage.h"

ConnexionPage::ConnexionPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}
