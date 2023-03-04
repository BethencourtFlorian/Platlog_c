#include "headers/user.h"

user::user()
{
    login = "new_user";
    password = "password";
    email = "new.user@mail.com";
    firstName = "John";
    lastName = "Doe";

    rights[0] = 1; rights[1] = 0; rights[2] = 0;
}

user::user(string new_login, string new_password, string new_email, string new_firstName, string new_lastName, int* new_rights)
{
    login = new_login;
    password = new_password;
    email = new_email;
    firstName = new_firstName;
    lastName = new_lastName;

    setRights(new_rights[0], new_rights[1], new_rights[2]);
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

int* user::getRights(){
    return rights;
}

int user::getRightRead(){
    return rights[0];
}

int user::getRightEdit(){
    return rights[1];
}

int user::getRightSudo(){
    return rights[2];
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
void user::setRights(int new_right_read, int new_right_edit, int new_right_sudo){
    setRightEdit(new_right_read);
    setRightRead(new_right_edit);
    setRightSudo(new_right_sudo);
}
void user::setRightRead(int new_right_read){
    if(new_right_read >= 1)
        rights[0] = 1;
    else
        rights[0] = 0;
}
void user::setRightEdit(int new_right_edit){
    if(new_right_edit >= 1)
        rights[1] = 1;
    else
        rights[1] = 0;
}
void user::setRightSudo(int new_right_sudo){
    if(new_right_sudo >= 1)
        rights[2] = 1;
    else
        rights[2] = 0;
}
