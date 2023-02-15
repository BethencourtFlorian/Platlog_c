#include "mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::onInfoSent(user& user)
{
    ui->title->setText(ui->title->text() + " " + QString::fromStdString(user.getFirstName()));
    ui->info_login->setText(ui->info_login->text() + " " + QString::fromStdString(user.getLogin()));
    ui->info_firstName->setText(ui->info_firstName->text() + " " + QString::fromStdString(user.getFirstName()));
    ui->info_lastName->setText(ui->info_lastName->text() + " " + QString::fromStdString(user.getLastName()));
    ui->info_mail->setText(ui->info_mail->text() + " " + QString::fromStdString(user.getEmail()));
}

void MainPage::on_button_deconnect_clicked()
{
    this->hide();
    ConnexionPage* connexionPage = new ConnexionPage();
    connexionPage->show();
}

