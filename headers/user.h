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
    user();
    user(string new_login, string new_password, string new_email, string new_firstName, string new_lastName);

    // Getters
    string getLogin();
    string getPassword();
    string getEmail();
    string getFirstName();
    string getLastName();

    //Setters
    void setLogin(string new_login);
    void setPassword(string new_password);
    void setEmail(string new_email);
    void setFirstName(string new_firstName);
    void setLastName(string new_lastName);
};

#endif // USER_H
