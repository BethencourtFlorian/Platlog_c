#include "headers/databaseadd.h"
#include "ui_databaseadd.h"

DatabaseAdd::DatabaseAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseAdd)
{
    ui->setupUi(this);
}

DatabaseAdd::~DatabaseAdd()
{
    delete ui;
}

void DatabaseAdd::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), "/home", tr("Data Base Files (*.db) (*.SQLite)"));
    ui->inputURL->setText(fileName);
}

void DatabaseAdd::onUserSent(User& user)
{
    this->user = user;
    unsigned int profileListSize = user.getProfiles().size();
    for (unsigned int i = 0 ; i < profileListSize ; i++)
    {
        ui->comboBox->addItem(user.getProfile(i)->getId());
    }
}

void DatabaseAdd::onUserWithSelectedSent(User& user, QString selectedItem)
{
    this->user = user;
    unsigned int profileListSize = user.getProfiles().size();
    for (unsigned int i = 0 ; i < profileListSize ; i++)
    {
        ui->comboBox->addItem(user.getProfile(i)->getId());
    }
    int index = ui->comboBox->findText(selectedItem);
    if (index >= 0)
        ui->comboBox->setCurrentIndex(index);
}


void DatabaseAdd::on_pushButton_2_clicked()
{

    if (ui->input_DBName->text().isEmpty() || ui->inputURL->text().isEmpty())
    {
        ui->label_error->setText("Veuillez remplir tous les champs");
    }
    else
    {
        Database* db = new Database(ui->input_DBName->text(), ui->inputURL->text());
        XMLParser::AddDatabase("myFile.xml",user, *db, ui->comboBox->currentIndex());
        emit destroyedDB(ui->comboBox->currentIndex());
        hide();
    }
}

