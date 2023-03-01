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
            users.appendChild(superUser);

            QDomElement userInfo = document.createElement("UserInfo");
            userInfo.setAttribute("Password", "root");
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
                    if(e.hasAttribute("Login")){
                        QString newLogin(e.attribute("Login"));
                        QDomNode userInfo = user.firstChild();
                        while(!userInfo.isNull()){
                            QDomElement eInfo = userInfo.toElement();
                            if(eInfo.tagName()=="UserInfo"){
                                if(eInfo.hasAttribute("Password")){
                                    QString newPassword(eInfo.attribute("Password"));
                                    if(newLogin == typedLogin && newPassword == typedPassword){
                                        foundUser.setLogin(newLogin.toStdString());
                                        foundUser.setPassword(newPassword.toStdString());
                                        foundUser.setEmail(eInfo.attribute("Email").toStdString());
                                        foundUser.setFirstName(eInfo.attribute("FirstName").toStdString());
                                        foundUser.setLastName(eInfo.attribute("LastName").toStdString());

                                        return 0;
                                    }
                                    else
                                        break; // Pas besoin de continuer à parcourir les profils si le login est pas bon
                                }
                            }
                            // Else balise profile
                            userInfo = userInfo.nextSibling();
                        }
                    }
                    else{
                        // Pas d'attribut login, problème dans le fichier
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
