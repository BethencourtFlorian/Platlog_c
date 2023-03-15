#include "newdatabase.h"
#include "ui_newdatabase.h"

NewDatabase::NewDatabase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewDatabase)
{
    ui->setupUi(this);
}

NewDatabase::~NewDatabase()
{
    delete ui;
}
