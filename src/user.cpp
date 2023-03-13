#include "headers/user.h"

list<Profile*> User::getProfiles() const
{
    return profiles;
}

void User::addProfile(Profile* newProfile)
{
    //Profile newProfile = Profile(id, loginUser);
    profiles.push_back(newProfile);
}
void User::deleteProfile(QString id)
{
    //Chercher le profil dans la liste
}

void User::clearProfiles(){
    while (!profiles.empty())
    {
        profiles.pop_front();
    }
}

User::User()
{
    login = "new_user";
    password = "password";
    email = "new.user@mail.com";
    firstName = "John";
    lastName = "Doe";

    rights[0] = 1; rights[1] = 0; rights[2] = 0;
}

User::User(QString new_login, QString new_password, QString new_email, QString new_firstName, QString new_lastName, int* new_rights)
{
    login = new_login;
    password = new_password;
    email = new_email;
    firstName = new_firstName;
    lastName = new_lastName;

    setRights(new_rights[0], new_rights[1], new_rights[2]);
}

// Getters
QString User::getLogin(){
    return login;
}
QString User::getPassword(){
    return password;
}
QString User::getEmail(){
    return email;
}
QString User::getFirstName(){
    return firstName;
}
QString User::getLastName(){
    return lastName;
}

int* User::getRights(){
    return rights;
}

int User::getRightRead(){
    return rights[0];
}

int User::getRightEdit(){
    return rights[1];
}

int User::getRightSudo(){
    return rights[2];
}


//Setters
void User::setLogin(QString new_login){
    login = new_login;
}
void User::setPassword(QString new_password){
    password = new_password;
}
void User::setEmail(QString new_email){
    email = new_email;
}
void User::setFirstName(QString new_firstName){
    firstName = new_firstName;
}
void User::setLastName(QString new_lastName){
    lastName = new_lastName;
}
void User::setRights(int new_right_read, int new_right_edit, int new_right_sudo){
    setRightEdit(new_right_read);
    setRightRead(new_right_edit);
    setRightSudo(new_right_sudo);
}
void User::setRightRead(int new_right_read){
    if(new_right_read >= 1)
        rights[0] = 1;
    else
        rights[0] = 0;
}
void User::setRightEdit(int new_right_edit){
    if(new_right_edit >= 1)
        rights[1] = 1;
    else
        rights[1] = 0;
}
void User::setRightSudo(int new_right_sudo){
    if(new_right_sudo >= 1)
        rights[2] = 1;
    else
        rights[2] = 0;
}
