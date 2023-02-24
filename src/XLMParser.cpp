#include "headers/XMLParser.h"
#include <QMainWindow>

int XMLParser::CheckUser(QDomDocument& document, QDomElement& users, QString filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text | QIODevice::ReadWrite))
    {
        qDebug() << "Failed to open writting";
        return -1;
    }
    else {
        if(file.size() == 0){
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
                                    qDebug() << newLogin;
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
                                            else
                                                reader.raiseError(QObject::tr("Users info should have 4 attributes (FirstName, LastName, Email and Password)"));
                                        }
                                    }
                                }
                                else
                                    reader.raiseError(QObject::tr("Users should have a login attribute"));
                            reader.skipCurrentElement();
                            }
                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else
                    reader.raiseError(QObject::tr("Incorrect file"));
            }
            file.close();
            return 0;
        }
    }
    return 1;
}

int XMLParser::CheckConnexion(QString filePath, user& foundUser, QString typedPassword, QString typedLogin){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
    {
        qDebug() << "Failed to open writting";
        return -1;
    }
    else {
        if(file.size() == 0){
            file.close();
            return 1;
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
                                                    foundUser.setLogin(newLogin.toStdString());
                                                    foundUser.setPassword(reader.attributes().value("Password").toString().toStdString());
                                                    foundUser.setEmail(reader.attributes().value("Email").toString().toStdString());
                                                    foundUser.setFirstName(reader.attributes().value("FirstName").toString().toStdString());
                                                    foundUser.setLastName(reader.attributes().value("LastName").toString().toStdString());

                                                    return 0;
                                                }
                                            }
                                            else
                                                reader.raiseError(QObject::tr("Users info should have 4 attributes (FirstName, LastName, Email and Password)"));
                                        }
                                    }
                                }
                                else
                                    reader.raiseError(QObject::tr("Users should have a login attribute"));
                            reader.skipCurrentElement();
                            }
                            }
                        }
                        else
                            reader.skipCurrentElement();
                    }
                }
                else
                    reader.raiseError(QObject::tr("Incorrect file"));
            }
            file.close();
            return 1;
        }
    }
    return 1;
}
