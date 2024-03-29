#include "headers/mainwindow.h"
#include "headers/XMLParser.h"
#include "qdom.h"
#include <QString>
#include "ui_mainwindow.h"

MainWindow::MainWindow(int XMLPassed, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , login("")
    , password("")
    , email("")
    , firstName("")
    , lastName("")
{
    XML = XMLPassed;
    this->setWindowTitle("Sign Up");
    ui->setupUi(this);
    ui->input_password->setEchoMode(QLineEdit::Password);
    connect(ui->button_inscription, &QPushButton::clicked, this, &MainWindow::storage);
    connect(ui->button_back, &QPushButton::clicked, this, &MainWindow::closeWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeWindow(){
    this->hide();
}

void MainWindow::onEditionSent(User user){
    login = user.getLogin();
    ui->button_inscription->setText("Update Account");
    disconnect(ui->button_inscription, &QPushButton::clicked, this, &MainWindow::storage);
    connect(ui->button_inscription, &QPushButton::clicked, this, emitUpdatedUser);
    ui->input_login->setText(user.getLogin());
    ui->input_password->setText(user.getPassword());
    ui->input_email->setText(user.getEmail());
    ui->input_prenom->setText(user.getFirstName());
    ui->input_nom->setText(user.getLastName());
}

void MainWindow::emitUpdatedUser(){
    QString filePath("myFile.xml");
    int rights[3] = {1,1,0};
    User userUpdated(ui->input_login->text(), ui->input_password->text(), ui->input_email->text(), ui->input_prenom->text(), ui->input_nom->text(), rights);
    XMLParser::editUserInfo(filePath, login, userUpdated);
    emit notifyUpdatedUser(userUpdated);
    this->close();
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
        ui->label_error->setText("You must fill all of the fields");
    }
    else
    {
        QString filePath("myFile.xml");
        QDomDocument document;
        // On ajoute le nouvel utilisateur dans le QDomDocument
        QDomElement user = document.createElement("User");
        user.setAttribute("Login", login);
        user.setAttribute("Password", password);

        QDomElement userInfo = document.createElement("UserInfo");
        userInfo.setAttribute("Email", email);
        userInfo.setAttribute("FirstName", firstName);
        userInfo.setAttribute("LastName", lastName);
        user.appendChild(userInfo);

        QDomElement userRights = document.createElement("UserRights");
        userRights.setAttribute("Read", 1);
        userRights.setAttribute("Edit", 0);
        userRights.setAttribute("Sudo", 0);
        user.appendChild(userRights);

        QDomElement profiles = document.createElement("Profiles");
        user.appendChild(profiles);

        if(XMLParser::AddUser(document, user, filePath) != 0){
            qDebug() << "Erreur de lecture du fichier";
        }

        // On ouvre le même fichier, en écriture cette fois-ci pour enregistrer le nouvel utlisateur dans le XML
        if(XML){
            QFile wFile(filePath);
            if (wFile.open(QIODevice::WriteOnly| QIODevice::Text | QIODevice::Truncate)){
                QTextStream stream(&wFile);
                stream << document.toString();
                wFile.close();
                this->hide();
            }
            else{
                qDebug() << "Erreur d'écriture du fichier";
            }
        }
        else{
            int rights[] = {1,0,0};
            User* newUser = new User(login, password, email, firstName, lastName, rights);
            emit notifyCloseSignup(newUser);
            this->hide();
        }
    }
}
