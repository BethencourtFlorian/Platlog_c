#include "headers/connexionpage.h"
#include "ui_connexionpage.h"
#include <QXmlStreamReader>

ConnexionPage::ConnexionPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
    connect(ui->button_connection, &QPushButton::clicked, this, &ConnexionPage::onClick);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}

int XMLParser(QString filePath, user& foundUser, QString typedPassword, QString typedLogin){
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

int ConnexionPage::onClick(){
    QString typedLogin = ui->input_login->text();
    QString typedPassword = ui->input_password->text();
    user foundUser;

    if (XMLParser("myFile.xml", foundUser, typedPassword, typedLogin) != 0)
        ui->label_error->setText("Login failed");
    else
    {
        MainPage *mpg = new MainPage;
        connect(this, &ConnexionPage::notifyInfoSent, mpg, &MainPage::onInfoSent);
        mpg->show();
        emit notifyInfoSent(foundUser);
        hide();

    }
    return 0;
}
