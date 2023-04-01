#include "headers/profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent, int XMLPassed) :
    QDialog(parent),
    ui(new Ui::Profile),
    id(""),
    loginUser("")
{
    XML = XMLPassed;
    ui->setupUi(this);
    ui->input_profile->setPlaceholderText("Nom");
}

Profile::Profile(const Profile& source){
    id = source.id;
    loginUser = source.loginUser;
}

Profile::~Profile()
{
    delete ui;
}

Profile::Profile(QString newId, QString newLoginUser){
    id = newId;
    loginUser = newLoginUser;
}

Profile &Profile::operator=(const Profile& source)
{
    id = source.id;
    loginUser = source.loginUser;
    return *this;
}

void Profile::addDb(Database* db){
    databases.push_back(db);
}

void Profile::onLoginSent(QString& loginPassed)
{
    loginUser = loginPassed;
}

void Profile::addProfileXML(){
    QDomDocument doc;
    QFile file("myFile.xml");
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDomNode user = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!user.isNull())
    {
        if (user.isElement())
        {
            QDomElement userElement = user.toElement();
            if (userElement.attribute("Login", "not set") == loginUser)
            {
                QDomNode info = user.firstChild();
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomElement profile = doc.createElement("Profile");
                        profile.setAttribute("id", ui->input_profile->text());
                        info.toElement().appendChild(profile);

                        if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                        {
                            QTextStream stream(&file);
                            stream << doc.toString();
                            file.close();
                        }
                    }
                    info = info.nextSibling();
                }
            }
        }
        user = user.nextSibling();
    }
}

void Profile::on_createProfile_clicked()
{
    if(XML){
        addProfileXML();
    }
    else{
        QString id(ui->input_profile->text());
        if(id == "")
            id == QString("default_id");
        emit sendNewId(id);
    }
    emit destroyed();
    hide();
}

QString Profile::getId() const
{
    return id;
}

void Profile::setId(const QString &newId)
{
    id = newId;
}

QString Profile::getLoginUser() const
{
    return loginUser;
}

void Profile::setLoginUser(const QString &newLoginUser)
{
    loginUser = newLoginUser;
}

std::list<Database*> Profile::getDatabases(){
    return databases;
}
