#include "headers/connexionpage.h"
#include "ui_connexionpage.h"


ConnexionPage::ConnexionPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionPage)
{
    ui->setupUi(this);
    connect(ui->button_connection, &QPushButton::clicked, this, &ConnexionPage::onClick);
}

ConnexionPage::~ConnexionPage()
{
    delete ui;
}

int ConnexionPage::onClick(){
    QDomDocument xmlDoc;

        QFile f("userInfo.xml");
        if (!f.open(QIODevice::ReadOnly))
        {
            qDebug() << "Error while opening user file";
            return 1;
        }
        xmlDoc.setContent(&f);
        f.close();

        QDomElement XMLRoot = xmlDoc.documentElement();
        QDomElement XMLUser = XMLRoot.firstChild().toElement();
        QString typedLogin = ui->input_login->text();
        QString typedPassword = ui->input_password->text();
        QString savedLogin = "";
        QString savedPassword = "";


        bool found = false;

        while(XMLUser.isNull() == false)
        {
            if (XMLUser.tagName() == "User")
            {
                while (!XMLUser.isNull() && !found)
                {
                    savedLogin = XMLUser.attribute("Login", "0");
                    savedPassword = XMLUser.attribute("Password", "Password");
                    if ((savedLogin == typedLogin) && (savedPassword == typedPassword))
                        found = true;

                    XMLUser = XMLUser.nextSibling().toElement();

                }
            }
            XMLUser = XMLUser.nextSibling().toElement();
        }
        if (!found)
            ui->label_error->setText("Login failed");
        else
        {
            emit notifyInfoSent(typedLogin);
            this->hide();
            MainPage mainPage;
            mainPage.setModal(true);
            mainPage.exec();
        }
        return 0;
}
