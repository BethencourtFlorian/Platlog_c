#include "headers/database.h"
#include "ui_database.h"

Database::Database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Database),
    name("MyDB"),
    path("")
{
    ui->setupUi(this);
}

Database::Database(QString newName, QString newPath){
    name = newName;
    path = newPath;
}

Database::Database(const Database& source){
    name = source.name;
    path= source.path;
}

Database &Database::operator=(const Database& source)
{
    name = source.name;
    path = source.path;
    return *this;
}

Database::~Database()
{
    delete ui;
}

QString Database::getName() const
{
    return name;
}

void Database::setName(const QString &newName)
{
    name = newName;
}

QString Database::getPath() const
{
    return path;
}

void Database::setPath(const QString &newPath)
{
    path = newPath;
}

void Database::showQuery(QString queryString){
    QSqlQuery* query = new QSqlQuery();
    bool selectQuery = queryString.startsWith("SELECT", Qt::CaseInsensitive);
    query->prepare(queryString);
    if (!query->exec())
        qDebug() << query->lastError().text();
    else if(selectQuery){
        QSqlQueryModel * modal = new QSqlTableModel;
        modal->setQuery(std::move(*query));
        ui->tableView->setModel(modal);
    }
}


