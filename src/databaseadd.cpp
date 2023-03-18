#include "headers/databaseadd.h"
#include "ui_databaseadd.h"

DatabaseAdd::DatabaseAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseAdd)
{
    ui->setupUi(this);
}

DatabaseAdd::~DatabaseAdd()
{
    delete ui;
}

void DatabaseAdd::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), "/home", tr("Data Base Files (*.db)"));
    ui->lineEdit_2->setText(fileName);
}

void DatabaseAdd::onUserSent(User& user)
{
    this->user = user;
    unsigned int profileListSize = user.getProfiles().size();
    for (unsigned int i = 0 ; i < profileListSize ; i++)
    {
        ui->comboBox->addItem(user.getProfile(i)->getId());
    }
}

void DatabaseAdd::onUserWithSelectedSent(User& user, QString selectedItem)
{
    this->user = user;
    unsigned int profileListSize = user.getProfiles().size();
    for (unsigned int i = 0 ; i < profileListSize ; i++)
    {
        ui->comboBox->addItem(user.getProfile(i)->getId());
    }
    int index = ui->comboBox->findText(selectedItem);
    if (index >= 0)
        ui->comboBox->setCurrentIndex(index);
}


void DatabaseAdd::on_pushButton_2_clicked()
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
    QDomNode userBal = root.firstChild().firstChild(); // <QtProject> -> <Users> -> <User>

    while (!userBal.isNull())
    {
        if (userBal.isElement())
        {
            QDomElement userElement = userBal.toElement();
            if (userElement.attribute("Login", "not set") == user.getLogin())
            {
                QDomNode info = userBal.firstChild(); // <User> -> <UserInfo>
                while(!info.isNull()){
                    if(info.nodeName() == "Profiles"){
                        QDomNode profile = info.firstChild(); // <Profiles> -> <Profile>
                        while (!profile.isNull())
                        {
                            if (profile.isElement())
                            {
                                QDomElement profileElement = profile.toElement();

                                if (profileElement.attribute("id", "not set") == user.getProfile(ui->comboBox->currentIndex())->getId())
                                {
                                    QDomElement db = doc.createElement("DB");
                                    db.setAttribute("name", ui->lineEdit->text());
                                    db.setAttribute("path", ui->lineEdit_2->text());
                                    profile.toElement().appendChild(db);

                                    if (file.open( QIODevice::WriteOnly | QIODevice::Text))
                                    {
                                        QTextStream stream(&file);
                                        stream << doc.toString();
                                        file.close();
                                    }
                                }
                            }
                            profile = profile.nextSibling();
                        }

                    }
                    info = info.nextSibling();
                }
            }
        }
        userBal = userBal.nextSibling();
    }

    emit destroyedDB(ui->comboBox->currentIndex());
    hide();

}

