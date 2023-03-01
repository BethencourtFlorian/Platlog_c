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
public:
    /**
     * @brief Constructeur par défaut
     *
     * Les attributs par défaut sont : \n
     *     login : "new_user" \n
     *     password : "password" \n
     *     email : "new.user@mail.com" \n
     *     firstName : "John" \n
     *     lastName : "Doe"
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
     */
    user(string new_login, string new_password, string new_email, string new_firstName, string new_lastName);

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
};

#endif // USER_H
