#include "headers/database.h"
#include "ui_database.h"

Database::Database(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Database),
    name(""),
    path("")
{
    ui->setupUi(this);
}

Database::Database(QString newName, QString newPath){
    name = newName;
    path = newPath;
    read = 1; edit = 1;
}

Database::Database(const Database& source){
    name = source.name;
    path= source.path;
    read = source.read;
    edit = source.edit;
}

Database &Database::operator=(const Database& source)
{
    name = source.name;
    path = source.path;
    read = source.read;
    edit = source.edit;
    return *this;
}

void Database::onDbSent(QSqlDatabase& db){
    if(db.open() && getRead() == 1){
        showQuery("SELECT name FROM sqlite_schema WHERE type ='table' AND name NOT LIKE 'sqlite_%';");

        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->lineEdit->setPlaceholderText("Insérer votre requête SQL");
        ui->tableView->show();
    }
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

int Database::getRead() const
{
    return read;
}

void Database::setRead(const int &newRead){
    read = newRead;
}

int Database::getEdit() const
{
    return edit;
}

void Database::setEdit(const int &newEdit){
    edit = newEdit;
}

void Database::showQuery(QString queryString){
    QSqlQuery* query = new QSqlQuery();
    bool selectQuery = queryString.startsWith("SELECT", Qt::CaseInsensitive);
    query->prepare(queryString);

    if(selectQuery){
        bool querySuccess = query->exec();
        bool readSuccess = getRead() == 1;
        if(readSuccess && querySuccess){
            QSqlQueryModel * modal = new QSqlTableModel;
            modal->setQuery(std::move(*query));
            ui->tableView->setModel(modal);
        }
        else{
            QMessageBox msgBox;
            msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
            QString errMsg("");
            if(!readSuccess){
                errMsg = "You don't have the rights for this type of query.";
                msgBox.setText(errMsg);
                msgBox.exec();
            }
            if(!querySuccess){
                errMsg = "Your query has failed";
                msgBox.setInformativeText("SQL Error : " + query->lastError().text());
                msgBox.setText(errMsg);
                msgBox.exec();
            }
        }
    }
    else{
        bool querySuccess = query->exec();
        bool editSuccess = getEdit() == 1;
        if(editSuccess && querySuccess){
            // Rien besoin d'afficher, c'est une requete INSERT ou DELETE
        }
        else{
            QMessageBox msgBox;
            msgBox.addButton(tr("Ok"), QMessageBox::ActionRole);
            QString errMsg("");
            if(!editSuccess){
                errMsg = "You don't have the rights for this type of query.";
                msgBox.setText(errMsg);
                msgBox.exec();
            }
            if(!querySuccess){
                errMsg = "Your query has failed";
                msgBox.setInformativeText("SQL Error : " + query->lastError().text());
                msgBox.setText(errMsg);
                msgBox.exec();
            }
        }
    }
}
