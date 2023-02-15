#include "headers/mainwindow.h"

#include "qdom.h"
#include <QFile>
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
        /*QByteArray hash = QCryptographicHash::hash(password.toLocal8Bit(), QCryptographicHash::Md5);
        qDebug() << hash;*/

        QDomDocument document;
        QDomElement root = document.createElement("Users");
        document.appendChild(root);

            QDomElement user = document.createElement("User");
            user.setAttribute("Login", login);
            user.setAttribute("Password", password);
            user.setAttribute("Email", email);
            user.setAttribute("FirstName", firstName);
            user.setAttribute("LastName", lastName);
            root.appendChild(user);

        QFile file("userInfo.xml");
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open writting";
            return -1;
        }
        else {
            QTextStream stream(&file);
            stream << document.toString();
            file.close();
            qDebug() << "Finished";
            this->hide();
            ConnexionPage connexionPage;
            connexionPage.setModal(true);
            connexionPage.exec();
        }
    }
    return 0;
}
