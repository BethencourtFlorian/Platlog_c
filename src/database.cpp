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

void Database::onDbSent(QSqlDatabase& db){
    db.open();

    showQuery("SELECT name FROM sqlite_schema WHERE type ='table' AND name NOT LIKE 'sqlite_%';");

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lineEdit->setPlaceholderText("Insérer votre requête SQL");
    ui->tableView->show();
}

void Database::on_pushButton_clicked(){
    showQuery(ui->lineEdit->text());
}

void Database::on_defaultButton_clicked(){
    showQuery("SELECT name FROM sqlite_schema WHERE type ='table' AND name NOT LIKE 'sqlite_%';");
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
