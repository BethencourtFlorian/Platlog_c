#include "headers/profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Profile),
    id(""),
    loginUser("")
{
    ui->setupUi(this);
}

Profile::~Profile()
{
    delete ui;
}


void Profile::onLoginSent(QString& loginPassed)
{
    loginUser = loginPassed;
}

void Profile::on_createProfile_clicked()
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

    QDomElement root = doc.documentElement();
    QDomNode user = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!user.isNull())
    {
        if (user.isElement())
        {
            QDomElement userElement = user.toElement();

            if (userElement.attribute("Login", "not set") == loginUser)
            {
                QDomElement profile = doc.createElement("Profile");
                profile.setAttribute("id", ui->input_profile->text());
                id = ui->input_profile->text(); // Optionnel ?
                userElement.appendChild(profile);

                if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << doc.toString();
                    file.close();
                }
            }
        }
        user = user.nextSibling();
    }
    emit destroyed();
    hide();
}

