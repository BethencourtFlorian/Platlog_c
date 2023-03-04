#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class user
{
private:
    string login;
    string password;
    string email;
    string firstName;
    string lastName;

    int rights[3];
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
    user();
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
    user(string new_login, string new_password, string new_email, string new_firstName, string new_lastName, int* new_rights);

    // Getters
    /**
     * @brief Renvoie le login de l'utilisateur
     * @return Une String contenant le login
     */
    string getLogin();
    /**
     * @brief Renvoie le mot de passe de l'utilisateur
     * @return Une String contenant le mot de passe
     */
    string getPassword();
    /**
     * @brief Renvoie l'email de l'utilisateur
     * @return Une String contenant l'email
     */
    string getEmail();
    /**
     * @brief Renvoie le prénom de l'utilisateur
     * @return Une String contenant le prénom
     */
    string getFirstName();
    /**
     * @brief Renvoie le nom de l'utilisateur
     * @return Une String contenant le nom
     */
    string getLastName();
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
     * @param new_login Une String contenant le nouveau login
     */
    void setLogin(string new_login);
    /**
     * @brief Modifie le mot de passe de l'utilisateur
     * @param new_password Une String contenant le nouveau mot de passe
     */
    void setPassword(string new_password);
    /**
     * @brief Modifie l'email de l'utilisateur
     * @param new_email Une String contenant le nouvel email
     */
    void setEmail(string new_email);
    /**
     * @brief Modifie le prénom de l'utilisateur
     * @param new_firstName Une String contenant le nouveau prénom
     */
    void setFirstName(string new_firstName);
    /**
     * @brief Modifie le nom de l'utilisateur
     * @param new_lastName Une String contenant le nouveau nom
     */
    void setLastName(string new_lastName);

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
};

#endif // USER_H
