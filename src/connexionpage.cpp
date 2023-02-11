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

        QFile f("myFile.xml");
        if (!f.open(QIODevice::ReadOnly))
        {
            qDebug() << "Erreur lors de l'ouverture du fichier";
            return 1;
        }
        xmlDoc.setContent(&f);
        f.close();

        QDomElement XMLRoot = xmlDoc.documentElement();
        QDomElement XMLNode = XMLRoot.firstChild().toElement();
        QString datas = "";

        while(XMLNode.isNull() == false)
        {
            qDebug() << XMLNode.tagName();
            if (XMLNode.tagName() == "User")
            {
                while (!XMLNode.isNull())
                {

                }
            }
        }

        qDebug() << "Connexion";
        return 0;
}
