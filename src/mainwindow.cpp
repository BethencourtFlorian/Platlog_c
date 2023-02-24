#include "headers/mainwindow.h"
#include "headers/XMLParser.h"
#include "qdom.h"
#include <QString>
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
        if(XMLParser::CheckUser(document, users, filePath) == 0){
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
        if (wFile.open(QIODevice::ReadWrite| QIODevice::Text | QIODevice::Truncate)){
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
