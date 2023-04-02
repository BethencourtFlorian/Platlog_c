#ifndef USER_H
#define USER_H

#include <QString>
#include <list>
#include "profile.h"

using namespace std;

class User
{
private:
    QString login;
    QString password;
    QString email;
    QString firstName;
    QString lastName;

    int rights[3];
    std::list<Profile*> profiles;
public:
    /**
     * @brief Constructeur par défaut
     *
     * Les attributs par défaut sont : \n
     *     login : "new_user" \n
     *     password : "password" \n
     *     email : "new.user@mail.com" \n
     *     firstName : "John" \n
     *     lastName : "Doe" \n
     *
     *     Dans l'ordre des droits on a Lecture, Edition et Super utilisateur\n
     *     Par défaut la lecture seulement est autorisée soit [1,0,0]
     */
    User();
    /**
     * @brief Constructeur par paramètre
     *
     * Associe chaque paramètre au bon attribut
     * @param new_login
     * @param new_password
     * @param new_email
     * @param new_firstName
     * @param new_lastName
     * @param new_rights
     */
    User(QString new_login, QString new_password, QString new_email, QString new_firstName, QString new_lastName, int* new_rights);

    // Getters
    /**
     * @brief Renvoie le login de l'utilisateur
     * @return Une QString contenant le login
     */
    QString getLogin();
    /**
     * @brief Renvoie le mot de passe de l'utilisateur
     * @return Une QString contenant le mot de passe
     */
    QString getPassword();
    /**
     * @brief Renvoie l'email de l'utilisateur
     * @return Une QString contenant l'email
     */
    QString getEmail();
    /**
     * @brief Renvoie le prénom de l'utilisateur
     * @return Une QString contenant le prénom
     */
    QString getFirstName();
    /**
     * @brief Renvoie le nom de l'utilisateur
     * @return Une QString contenant le nom
     */
    QString getLastName();
    /**
     * @brief Renvoie la liste des droits de l'utilisateur
     * @return Une liste d'entiers contenant les droits [READ,EDIT,SUDO], 0 ou 1
     */
    int* getRights();
    /**
     * @brief Renvoie le droit en lecture de l'utilisateur
     * @return Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    int getRightRead();
    /**
     * @brief Renvoie le droit en édition de l'utilisateur
     * @return Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    int getRightEdit();
    /**
     * @brief Renvoie le droit total de l'utilisateur
     * @return Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    int getRightSudo();

    //Setters
    /**
     * @brief Modifie le login de l'utilisateur
     * @param new_login Une QString contenant le nouveau login
     */
    void setLogin(QString new_login);
    /**
     * @brief Modifie le mot de passe de l'utilisateur
     * @param new_password Une QString contenant le nouveau mot de passe
     */
    void setPassword(QString new_password);
    /**
     * @brief Modifie l'email de l'utilisateur
     * @param new_email Une QString contenant le nouvel email
     */
    void setEmail(QString new_email);
    /**
     * @brief Modifie le prénom de l'utilisateur
     * @param new_firstName Une QString contenant le nouveau prénom
     */
    void setFirstName(QString new_firstName);
    /**
     * @brief Modifie le nom de l'utilisateur
     * @param new_lastName Une QString contenant le nouveau nom
     */
    void setLastName(QString new_lastName);

    /**
     * @brief Modifie la liste des droits de l'utilisateur
     * @param Une liste d'entiers contenant les droits [READ,EDIT,SUDO], 0 ou 1
     */
    void setRights(int new_right_read, int new_right_edit, int new_right_sudo);
    /**
     * @brief Modifie le droit en lecture de l'utilisateur
     * @param Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    void setRightRead(int new_right_read);
    /**
     * @brief Modifie le droit en édition de l'utilisateur
     * @param Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    void setRightEdit(int new_right_edit);
    /**
     * @brief Modifie le droit total de l'utilisateur
     * @param Un entier (0 ou 1) pour indiquer ou pas l'autorisation
     */
    void setRightSudo(int new_right_sudo);

    /**
     * @brief Retourne la liste des profiles pour un utilisateur
     * @return std::list<Profile*> liste des profils de l'utilisateur
     */
    std::list<Profile*> getProfiles() const;

    /**
     * @brief Retourne un profile donné pour un utilisateur
     * @param _i ID du profil à retourner
     * @return std::list<Profile*> liste des profils de l'utilisateur
     */
    Profile* getProfile(int _i);

    /**
     * @brief Ajoute un profil à l'utilisateur courant
     * @param newProfile profil à ajouter
     * @return void
     */
    void addProfile(Profile* newProfile);

    /**
     * @brief Supprime un profil de l'utilisateur courant
     * @param id ID du profil à supprimer
     * @return void
     */
    void deleteProfile(QString id);

    /**
     * @brief Supprime tous les profils pour un utilisateur
     * @return void
     */
    void clearProfiles();
};

#endif // USER_H
