#include "headers/dbcreatepage.h"
#include "ui_dbcreatepage.h"

DBCreatePage::DBCreatePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DBCreatePage)
{
    ui->setupUi(this);
    auto QVbox = new QVBoxLayout();
    auto QHbox = new QHBoxLayout();
    auto QCombo = new QComboBox();

    QHbox->addWidget(QCombo);
    QHbox->addWidget(new QLineEdit());
    QVbox->addLayout(QHbox);

    setLayout(QVbox);
}

DBCreatePage::~DBCreatePage()
{
    delete ui;
}

void DBCreatePage::on_input_COLNUM_valueChanged(int colnum)
{

}

