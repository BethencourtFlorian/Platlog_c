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

void MainWindow::storage()
{
    login = ui->input_login->text();
    password = ui->input_password->text();
    email = ui->input_email->text();
    firstName = ui->input_prenom->text();
    lastName = ui->input_nom->text();

    if (login.isEmpty() || password.isEmpty() || email.isEmpty() || firstName.isEmpty() || lastName.isEmpty())
    {
        ui->label_error->setText("Veuillez remplir tous les champs");
    }
    else
    {
        QString filePath("myFile.xml");
        QDomDocument document;
        // On ajoute le nouvel utilisateur dans le QDomDocument
        QDomElement user = document.createElement("User");
        user.setAttribute("Login", login);

        QDomElement userInfo = document.createElement("UserInfo");
        userInfo.setAttribute("Password", password);
        userInfo.setAttribute("Email", email);
        userInfo.setAttribute("FirstName", firstName);
        userInfo.setAttribute("LastName", lastName);
        user.appendChild(userInfo);

        if(XMLParser::AddUser(document, user, filePath) != 0){
            qDebug() << "Erreur de lecture du fichier";
        }

        // On ouvre le même fichier, en écriture cette fois-ci pour enregistrer le nouvel utlisateur dans le XML
        QFile wFile(filePath);
        if (wFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate)){
            QTextStream stream(&wFile);
            stream << document.toString();
            wFile.close();
            this->hide();
            ConnexionPage* connexionPage = new ConnexionPage;
            connexionPage->show();
        }
        else{
            qDebug() << "Erreur d'écriture du fichier";
        }
    }
}
