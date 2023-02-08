#include "headers/user.h"

user::user()
{
    login = "new_user";
    password = "password";
    email = "new.user@mail.com";
    firstName = "John";
    lastName = "Doe";
}

user::user(string new_login, string new_password, string new_email, string new_firstName, string new_lastName)
{
    login = new_login;
    password = new_password;
    email = new_email;
    firstName = new_firstName;
    lastName = new_lastName;
}

// Getters
string user::getLogin(){
    return login;
}
string user::getPassword(){
    return password;
}
string user::getEmail(){
    return email;
}
string user::getFirstName(){
    return firstName;
}
string user::getLastName(){
    return lastName;
}

//Setters
void user::setLogin(string new_login){
    login = new_login;
}
void user::setPassword(string new_password){
    password = new_password;
}
void user::setEmail(string new_email){
    email = new_email;
}
void user::setFirstName(string new_firstName){
    firstName = new_firstName;
}
void user::setLastName(string new_lastName){
    lastName = new_lastName;
}
