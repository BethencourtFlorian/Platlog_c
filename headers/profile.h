#ifndef PROFILE_H
#define PROFILE_H

#include <list>
#include <QDomDocument>
#include <QFile>
#include <QObject>
#include <QDialog>
#include "database.h"

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr, int XML = 1);

    /**
     * @brief Constructeur de recopie d'un profil
     */
    Profile(const Profile&);

    /**
     * @brief Constructeur par paramètre
     * Associe chaque paramètre au bon attribut
     *
     * @param id
     * @param loginUser
     */
    Profile(QString id, QString loginUser);

    ~Profile();

    /**
     * @brief Surcharge de l'opérateur = pour un profil
     *
     * @param source
     */
    Profile &operator=(const Profile& source);

    /**
     * @brief Ajoute une base de données pour le profil courant
     *
     * @param db base de données à ajouter
     * @return void
     */
    void addDb(Database* db);

    /**
     * @brief Retourne la liste des bases de données d'un profil
     *
     * @return std::list<Database*> liste des bases de données d'un profil
     */
    std::list<Database*> getDbs();

    /**
     * @brief Ajoute un profil dans le fichier XML
     */
    void addProfileXML();

    /**
     * @brief Getter de l'ID d'un profil
     * @return QString ID du profil
     */
    QString getId() const;

    /**
     * @brief Setter de l'ID d'un profil
     * @param newId ID du profil
     */
    void setId(const QString &newId);

    /**
     * @brief Getter du login de l'utilisateur d'un profil
     * @return QString Login de l'utilisateur attaché au profil
     */
    QString getLoginUser() const;

    /**
     * @brief Setter du login de l'utilisateur d'un profil
     * @param newLoginUser Login de l'utilisateur du profil
     */
    void setLoginUser(const QString &newLoginUser);

    /**
     * @brief Retourne la liste des bases de données du profil
     * @return std::list<Database*> liste de bases de données du profil
     */
    std::list<Database*> getDatabases();

public slots:

    /**
     * @brief Gère le passage du Login d'une fenêtre à l'autre
     * @param login login de l'utilisateur
     */
    void onLoginSent(QString& login);

private slots:
    /**
     * @brief Listener du bouton de création d'un profil
     */
    void on_createProfile_clicked();

signals:
    /**
     * @brief signal d'envoi d'un ID
     * @param id id du profile à transmettre
     */
    void sendNewId(QString id);

    /**
     * @brief signal appelé lorsqu'un profil est supprimé
     */
    void destroyedProfile();

private:
    Ui::Profile *ui;
    QString id;
    QString loginUser;
    std::list<Database*> databases;
    int XML = 1;
};

#endif // PROFILE_H
