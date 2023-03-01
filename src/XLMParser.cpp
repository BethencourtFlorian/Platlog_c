#include "headers/XMLParser.h"
#include <QMainWindow>

int XMLParser::CheckUser(QDomDocument& document, QDomElement& users, QString filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        // Erreur d'ouverture du fichier
        return -1;
    }
    else {
        if(file.size() == 0){
            // Si le fichier est vide on crée un super utilisateur
            QDomElement superUser = document.createElement("User");
            superUser.setAttribute("Login", "su");
            users.appendChild(superUser);

            QDomElement userInfo = document.createElement("UserInfo");
            userInfo.setAttribute("Password", "root");
            userInfo.setAttribute("Email", "");
            userInfo.setAttribute("FirstName", "Admin");
            userInfo.setAttribute("LastName", "");
            superUser.appendChild(userInfo);

            file.close();
            return 0;
        }
        else{
            // Sinon on parcourt la liste des utilisateurs existants et on les rajoute au QDomDocument
            QString newLogin = "";
            QXmlStreamReader reader(&file);
            if (reader.readNextStartElement()) {
                if (reader.name() == QString("QtProject")){
                    while(reader.readNextStartElement()){
                        if(reader.name() ==  QString("Users")){
                            while(reader.readNextStartElement()){
                                if(reader.name() ==  QString("User")){
                                    if(reader.attributes().hasAttribute("Login")){
                                        newLogin = reader.attributes().value("Login").toString();
                                        while(reader.readNextStartElement()){
                                            if(reader.name() ==  QString("UserInfo")){
                                                if(reader.attributes().hasAttribute("FirstName") &&
                                                reader.attributes().hasAttribute("LastName") &&
                                                reader.attributes().hasAttribute("Email") &&
                                                reader.attributes().hasAttribute("Password")){

                                                    QDomElement user = document.createElement("User");
                                                    user.setAttribute("Login", newLogin);
                                                    users.appendChild(user);

                                                    QDomElement userInfo = document.createElement("UserInfo");
                                                    userInfo.setAttribute("Password", reader.attributes().value("Password").toString());
                                                    userInfo.setAttribute("Email", reader.attributes().value("Email").toString());
                                                    userInfo.setAttribute("FirstName", reader.attributes().value("FirstName").toString());
                                                    userInfo.setAttribute("LastName", reader.attributes().value("LastName").toString());
                                                    user.appendChild(userInfo);

                                                }
                                                else{
                                                    /*
                                                     * Chaque utilisateur doit posséder les 4 attributs suivants : FirstName, LastName, Email et Password
                                                     * Situés dans la balise "UserInfo" associée
                                                    */
                                                    return -1;
                                                }
                                            }
                                        }
                                    }
                                    else{
                                        // Chaque utilisateur doit posséder un attribut Login
                                        return -1;
                                    }
                                reader.skipCurrentElement();
                                }
                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else{
                    // Mauvais fichier
                    return -1;
                }
            }
            file.close();
            return 0;
        }
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
            QXmlStreamReader reader(&file);
            if (reader.readNextStartElement()) {
                if (reader.name() == QString("QtProject")){
                    while(reader.readNextStartElement()){
                        if(reader.name() ==  QString("Users")){
                            while(reader.readNextStartElement()){
                                if(reader.name() ==  QString("User")){
                                    if(reader.attributes().hasAttribute("Login")){
                                        QString newLogin = reader.attributes().value("Login").toString();
                                        while(reader.readNextStartElement()){
                                            if(reader.name() ==  QString("UserInfo")){
                                                if(reader.attributes().hasAttribute("FirstName") &&
                                                reader.attributes().hasAttribute("LastName") &&
                                                reader.attributes().hasAttribute("Email") &&
                                                reader.attributes().hasAttribute("Password")){
                                                    if(newLogin == typedLogin && reader.attributes().value("Password").toString() == typedPassword){
                                                        // Si on trouve une correspondance, on remplit les informations de l'utilisateur dans foundUser
                                                        foundUser.setLogin(newLogin.toStdString());
                                                        foundUser.setPassword(reader.attributes().value("Password").toString().toStdString());
                                                        foundUser.setEmail(reader.attributes().value("Email").toString().toStdString());
                                                        foundUser.setFirstName(reader.attributes().value("FirstName").toString().toStdString());
                                                        foundUser.setLastName(reader.attributes().value("LastName").toString().toStdString());

                                                        return 0;
                                                    }
                                                }
                                                else{
                                                    /*
                                                     * Chaque utilisateur doit posséder les 4 attributs suivants : FirstName, LastName, Email et Password
                                                     * Situés dans la balise "UserInfo" associée
                                                    */
                                                    return -1;
                                                }
                                            }
                                        }
                                    }
                                    else{
                                        // Chaque utilisateur doit posséder un attribut Login
                                        return -1;
                                    }
                                reader.skipCurrentElement();
                                }
                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else{
                    // Mauvais fichier
                    return -1;
                }
            }
            // Aucune correspondance trouvée, mauvais login ou mdp
            file.close();
            return -1;
        }
    }
}
