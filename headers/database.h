#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
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
    void setName(const QString &newName);
    void setPath(const QString &newPath);

    void showQuery(QString query);

public slots:
    void onDbSent(QSqlDatabase& db);
    void on_pushButton_clicked();
    void on_defaultButton_clicked();

private:
    Ui::Database *ui;
    QString name;
    QString path;

};

#endif // DATABASE_H
