#include "headers/XMLParser.h"
#include <QMainWindow>

int XMLParser::AddUser(QDomDocument& document, QDomElement newUser, QString filePath){
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite| QIODevice::Text))
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

int XMLParser::CheckConnexion(QString filePath, User& foundUser, QString typedPassword, QString typedLogin){
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
                                    foundUser.setLogin(newLogin);
                                    foundUser.setPassword(newPassword);
                                    foundUser.setEmail(eInfo.attribute("Email"));
                                    foundUser.setFirstName(eInfo.attribute("FirstName"));
                                    foundUser.setLastName(eInfo.attribute("LastName"));
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

void XMLParser::AddDatabase(QString path, User& user, Database& database, int idProfile)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode userBal = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!userBal.isNull())
    {
        if (userBal.isElement())
        {
            QDomElement userElement = userBal.toElement();
            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                QDomNode info = userBal.firstChild(); // <User> -> <UserInfo>
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomNode profile = info.firstChild(); // <Profiles> -> <Profile>
                        while (!profile.isNull())
                        {
                            if (profile.isElement())
                            {
                                QDomElement profileElement = profile.toElement();
                                //ui->comboBox->currentIndex())->getId()
                                if (profileElement.attribute("id", "not set") == user.getProfile(idProfile)->getId())
                                {
                                    QDomElement db = doc.createElement("DB");
                                    //ui->input_DBName->text()
                                    //ui->inputURL->text()
                                    db.setAttribute("name", database.getName());
                                    db.setAttribute("path", database.getPath());
                                    profile.toElement().appendChild(db);

                                    if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                                    {
                                        QTextStream stream(&file);
                                        stream << doc.toString();
                                        file.close();
                                    }
                                }
                            }
                            profile = profile.nextSibling();
                        }
                    }
                    info = info.nextSibling();
                }
            }
        }
        userBal = userBal.nextSibling();
    }
}


Database* XMLParser::searchDatabase(QString path, User& user, QString profileName, QString databaseName)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode userBal = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!userBal.isNull())
    {
        if (userBal.isElement())
        {
            QDomElement userElement = userBal.toElement();
            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                QDomNode info = userBal.firstChild(); // <User> -> <UserInfo>
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomNode profile = info.firstChild(); // <Profiles> -> <Profile>
                        while (!profile.isNull())
                        {
                            if (profile.isElement())
                            {
                                QDomElement profileElement = profile.toElement();
                                //ui->comboBox->currentIndex())->getId()
                                if (profileElement.attribute("id", "not set") == profileName)
                                {
                                    QDomNode dbs = profile.firstChild();
                                    while (!dbs.isNull())
                                    {
                                        if (dbs.isElement())
                                        {
                                            QDomElement dbElement = dbs.toElement();
                                            if (dbElement.attribute("name", "not set") == databaseName)
                                            {
                                                return new Database(databaseName, dbElement.attribute("path", "not set"));
                                            }
                                        }
                                        dbs = dbs.nextSibling();
                                    }
                                }
                            }
                            profile = profile.nextSibling();
                        }
                    }
                    info = info.nextSibling();
                }
            }
        }
        userBal = userBal.nextSibling();
    }
}


void XMLParser::fillUser(QString path, User& user)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode userNode = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while ( !userNode.isNull())
    {
        if (userNode.isElement())
        {
            QDomElement userElement = userNode.toElement();

            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                user.clearProfiles();
                QDomNode infoNode = userNode.firstChild();
                if(infoNode.isElement()){
                    while(!infoNode.isNull()){
                        if(infoNode.nodeName() == "Profiles"){
                            QDomNode profileNode = infoNode.firstChild();
                            while(!profileNode.isNull()){
                                QDomElement profileElement = profileNode.toElement();
                                Profile* newProfile = new Profile(profileElement.attribute("id"), user.getLogin());
                                QDomNode dbNode = profileNode.firstChild();
                                while(!dbNode.isNull()){
                                    QDomElement dbElement = dbNode.toElement();
                                    Database* newDatabase = new Database(dbElement.attribute("name"), dbElement.attribute("path"));
                                    newProfile->addDb(newDatabase);
                                    dbNode = dbNode.nextSibling();
                                }
                                user.addProfile(newProfile);
                                profileNode = profileNode.nextSibling();
                            }
                        }
                        infoNode = infoNode.nextSibling();
                    }
                }
            }
        }
        userNode = userNode.nextSibling();
    }
}

void XMLParser::deleteProfileById(QString path, User& user, QString profileName)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode userBal = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!userBal.isNull())
    {
        if (userBal.isElement())
        {
            QDomElement userElement = userBal.toElement();
            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                QDomNode info = userBal.firstChild(); // <User> -> <UserInfo>
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomNode profile = info.firstChild(); // <Profiles> -> <Profile>
                        while (!profile.isNull())
                        {
                            if (profile.isElement())
                            {
                                QDomElement profileElement = profile.toElement();
                                //ui->comboBox->currentIndex())->getId()
                                if (profileElement.attribute("id", "not set") == profileName)
                                {
                                    info.removeChild(profileElement);
                                    if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                                    {
                                        QTextStream stream(&file);
                                        stream << doc.toString();
                                        file.close();
                                        return;
                                    }
                                }
                            }
                            profile = profile.nextSibling();
                        }
                    }
                    info = info.nextSibling();
                }
            }
        }
        userBal = userBal.nextSibling();
    }
}

void XMLParser::deleteDatabaseById(QString path, User& user, QString profileName, QString databaseName)
{
    QDomDocument doc;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode userBal = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!userBal.isNull())
    {
        if (userBal.isElement())
        {
            QDomElement userElement = userBal.toElement();
            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                QDomNode info = userBal.firstChild(); // <User> -> <UserInfo>
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomNode profile = info.firstChild(); // <Profiles> -> <Profile>
                        while (!profile.isNull())
                        {
                            if (profile.isElement())
                            {
                                QDomElement profileElement = profile.toElement();
                                //ui->comboBox->currentIndex())->getId()
                                if (profileElement.attribute("id", "not set") == profileName)
                                {
                                    QDomNode dbs = profile.firstChild();
                                    while (!dbs.isNull())
                                    {
                                        if (dbs.isElement())
                                        {
                                            QDomElement dbElement = dbs.toElement();
                                            if (dbElement.attribute("name", "not set") == databaseName)
                                            {
                                                profileElement.removeChild(dbElement);
                                                if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                                                {
                                                    QTextStream stream(&file);
                                                    stream << doc.toString();
                                                    file.close();
                                                    return;
                                                }
                                            }
                                        }
                                        dbs = dbs.nextSibling();
                                    }
                                }
                            }
                            profile = profile.nextSibling();
                        }
                    }
                    info = info.nextSibling();
                }
            }
        }
        userBal = userBal.nextSibling();
    }
}
