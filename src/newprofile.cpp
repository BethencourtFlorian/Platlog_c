#include "headers/newprofile.h"
#include "ui_newprofile.h"

NewProfile::NewProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProfile),
    username("")
{
    ui->setupUi(this);
}

NewProfile::~NewProfile()
{
    delete ui;
}


void NewProfile::onUsernameSent(QString& usernamePassed)
{
    username = usernamePassed;
    qDebug() << username;
}

void NewProfile::on_createProfile_clicked()
{
    QDomDocument doc;
    QFile file("myFile.xml");
    if (!file.open(QIODevice::ReadOnly))
        qDebug() << "Le fichier n'a pas pu être ouvert";
    if (!doc.setContent(&file)) {
        file.close();
        qDebug() << "Le fichier n'a pas pu être parsé";
    }
    file.close();

    QDomElement documentElement = doc.documentElement();
    QDomNode node = documentElement.firstChild().firstChild();

    while ( !node.isNull())
    {
        if (node.isElement())
        {
            QDomElement element = node.toElement();
            qDebug() << "ELEMENT" << element.tagName();
            qDebug() << "ELEMENT ATTRIBUTE NAME" << element.attribute("Login", "not set");

            if (element.attribute("Login", "not set") == username)
            {
                QDomElement profile = doc.createElement("Profile");
                profile.setAttribute("id", ui->input_profile->text());
                element.appendChild(profile);

                if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << doc.toString();
                    file.close();
                }
            }
        }
        if (node.isText())
        {
            QDomText text = node.toText();
            qDebug() << text.data();
        }
        node = node.nextSibling();
    }
    emit destroyed();
    hide();
}

