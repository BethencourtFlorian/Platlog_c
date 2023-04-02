#ifndef DATABASEADD_H
#define DATABASEADD_H

#include <QWidget>
#include <QFileDialog>
#include "user.h"
#include "XMLParser.h"

namespace Ui {
class DatabaseAdd;
}

class DatabaseAdd : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseAdd(int XML = 1,QWidget *parent = nullptr);
    ~DatabaseAdd();

public slots:
    /**
     * @brief Gère la réception du signal transférant un utilisateur
     * @param user utilisateur reçu
     */
    void onUserSent(User& user);

    /**
     * @brief Gère la réception du signal transférant un utilisateur et un profil donné
     * @param user utilisateur reçu
     * @param selectedItem nom du profil reçu
     */
    void onUserWithSelectedSent(User& user, QString selectedItem);

private slots:

    /**
     * @brief Renvoie vers la page de recherche d'une base de données
     */
    void on_pushButton_clicked();

    /**
     * @brief Gère l'ajout de la base de données
     */
    void on_pushButton_2_clicked();

signals:
    /**
     * @brief Envoie un signal avec comme conteneur la base de données créée
     * @param database base de données à transférer
     */
    void sendNewDatabase(Database* database);

    /**
     * @brief Signale la suppresion d'une base de données
     * @param idProfile id du profile où la base de données à été supprimée
     */
    void destroyedDB(unsigned int idProfile);

private:
    int XML;
    Ui::DatabaseAdd *ui;
    User user;
};

#endif // DATABASEADD_H
