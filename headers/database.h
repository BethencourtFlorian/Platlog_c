#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDialog>
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
    void setName(const QString &newName);
    void setPath(const QString &newPath);

    /**
     * @brief Affiche le résultat de la requête sur la base de données en fonction de la requête saisie
     * @param queryString requête entrée par l'utilisateur
     */
    void showQuery(QString queryString);

public slots:
    /**
     * @brief Gère la réception d'une base de données à manipuler
     * @param db base de données reçue
     */
    void onDbSent(QSqlDatabase& db);

    /**
     * @brief Gère l'affichage du résultat de la requête
     */
    void on_pushButton_clicked();

    /**
     * @brief Gère l'affichage des tables de la base de données
     */
    void on_defaultButton_clicked();

private:
    Ui::Database *ui;
    QString name;
    QString path;

};

#endif // DATABASE_H
