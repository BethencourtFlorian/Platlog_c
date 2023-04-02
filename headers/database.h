#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class Database;
}

class Database : public QDialog
{
    Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    Database(QString newName, QString newPath);
    Database(const Database& source);
    Database &operator=(const Database& source);

    ~Database();

    QString getName() const;
    QString getPath() const;
    int getRead() const;
    int getEdit() const;

    void setName(const QString &newName);
    void setPath(const QString &newPath);
    void setRead(const int &newRead);
    void setEdit(const int &newEdit);
    void showQuery(QString queryString);

public slots:
    void onDbSent(QSqlDatabase& db);
    void on_pushButton_clicked();
    void on_defaultButton_clicked();

private:
    Ui::Database *ui;
    QString name;
    QString path;
    int read = 1;
    int edit = 1;
};

#endif // DATABASE_H
