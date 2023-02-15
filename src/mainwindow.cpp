#include "headers/mainwindow.h"

#include "qdom.h"
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , login("")
    , password("")
    , email("")
    , firstName("")
    , lastName("")
{
    ui->setupUi(this);
    ui->input_password->setEchoMode(QLineEdit::Password);
    connect(ui->button_inscription, &QPushButton::clicked, this, &MainWindow::storage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int XMLParser(QDomDocument& document, QDomElement& users, QString filePath){
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly| QIODevice::Text))
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

int MainWindow::storage()
{
    login = ui->input_login->text();
    password = ui->input_password->text();
    email = ui->input_email->text();
    firstName = ui->input_prenom->text();
    lastName = ui->input_nom->text();

    if (login.isEmpty() || password.isEmpty() || email.isEmpty() || firstName.isEmpty() || lastName.isEmpty())
    {
        ui->label_error->setText("Registration failed");
    }
    else
    {
        QDomDocument document;
        QDomElement root = document.createElement("QtProject");
        document.appendChild(root);

        QDomElement users = document.createElement("Users");
        root.appendChild(users);

        QString filePath("myFile.xml");
        if(XMLParser(document, users, filePath) == 0){
            // Adding the new user to the xml
            QDomElement user = document.createElement("User");
            user.setAttribute("Login", login);
            users.appendChild(user);

            QDomElement userInfo = document.createElement("UserInfo");
            userInfo.setAttribute("Password", password);
            userInfo.setAttribute("Email", email);
            userInfo.setAttribute("FirstName", firstName);
            userInfo.setAttribute("LastName", lastName);
            user.appendChild(userInfo);
        }

        QFile wFile(filePath);
        if (!wFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate)){
            // Adding the new User
            QDomElement user = document.createElement("User");
            user.setAttribute("Login", login);
            user.setAttribute("Password", password);
            user.setAttribute("Email", email);
            user.setAttribute("FirstName", firstName);
            user.setAttribute("LastName", lastName);
            root.appendChild(user);

            QTextStream stream(&wFile);
            stream << document.toString();
            wFile.close();
            qDebug() << "Finished";
            this->hide();
            ConnexionPage* connexionPage = new ConnexionPage;
            connexionPage->show();
        }
        else{
            qDebug() << "Failed to open writting";
            return -1;
        }
    }
    return 0;
}
