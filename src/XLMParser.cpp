#include "headers/XMLParser.h"
#include <QMainWindow>

int XMLParser::AddUser(QDomDocument& document, QDomElement newUser, QString filePath){
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        if(file.size() == 0){
            // Si le fichier est vide on crée un super utilisateur
            QDomElement root = document.createElement("QtProject");
            document.appendChild(root);

            QDomElement users = document.createElement("Users");
            root.appendChild(users);

            QDomElement superUser = document.createElement("User");
            superUser.setAttribute("Login", "su");
            superUser.setAttribute("Password", "root");
            users.appendChild(superUser);

            QDomElement userInfo = document.createElement("UserInfo");
            userInfo.setAttribute("Email", "");
            userInfo.setAttribute("FirstName", "Admin");
            userInfo.setAttribute("LastName", "");
            superUser.appendChild(userInfo);

            QDomElement userRights = document.createElement("UserRights");
            userRights.setAttribute("Read", 1);
            userRights.setAttribute("Edit", 1);
            userRights.setAttribute("Sudo", 1);
            superUser.appendChild(userRights);

            // On ajoute le nouvel utilisateur donné en paramètre
            users.appendChild(newUser);
        }
        else{
            document.setContent(&file, true);
            QDomNode root = document.firstChild();
            QDomNode users = root.firstChild();
            users.insertAfter(newUser, users.lastChild());
        }
        file.close();
        return 0;
    }
    else{
        // Erreur d'ouverture du fichier
        qDebug() << "Erreur d'ouverture du fichier";
        return -1;
    }
}

int XMLParser::CheckConnexion(QString filePath, user& foundUser, QString typedPassword, QString typedLogin){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        // Erreur d'ouverture du fichier
        return -1;
    }
    else {
        if(file.size() == 0){
            // Fichier vide, inutile de rechercher une correspondance
            file.close();
            return -1;
        }
        else{
            QDomDocument document;
            document.setContent(&file, true);
            QDomNode root = document.firstChild();
            QDomNode users = root.firstChild();
            QDomNode user = users.firstChild();

            while (!user.isNull()) {
                if (user.isElement()) {
                    QDomElement e = user.toElement();
                    if(e.hasAttribute("Login") && e.hasAttribute("Password")){
                        QString newLogin(e.attribute("Login"));
                        QString newPassword(e.attribute("Password"));
                        if(newLogin == typedLogin && newPassword == typedPassword){
                            QDomNode userInfo = user.firstChild();
                            while(!userInfo.isNull()){
                                QDomElement eInfo = userInfo.toElement();
                                if(eInfo.tagName()=="UserInfo"){
                                    foundUser.setLogin(newLogin.toStdString());
                                    foundUser.setPassword(newPassword.toStdString());
                                    foundUser.setEmail(eInfo.attribute("Email").toStdString());
                                    foundUser.setFirstName(eInfo.attribute("FirstName").toStdString());
                                    foundUser.setLastName(eInfo.attribute("LastName").toStdString());
                                }
                                else if(eInfo.tagName() == "UserRights"){
                                    foundUser.setRights(eInfo.attribute("Read").toInt(), eInfo.attribute("Edit").toInt(), eInfo.attribute("Sudo").toInt());
                                }
                                // Else balise profile
                                userInfo = userInfo.nextSibling();
                            }
                            return 0;
                        }
                    }
                    else{
                        // Pas d'attribut login ou password, problème dans le fichier
                        return -1;
                    }
                }
                user = user.nextSibling();
            }
            // Aucune correspondance trouvée, mauvais login ou mdp
            file.close();
            return -1;
        }
    }
}
