#include "headers/mainpage.h"
#include "ui_mainpage.h"

MainPage::MainPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainPage)
{
    ui->setupUi(this);
    this->setWindowTitle("Accueil");

}

MainPage::~MainPage()
{
    delete ui;
}

void MainPage::onInfoSent(user& user)
{
    // Chaque champ de la vue est remplie avec les informations de l'utilisateur récupérées par la vue Connexion
    ui->title->setText(QString::fromStdString(user.getFirstName()) + "'s " + ui->title->text());
    ui->info_login->setText(ui->info_login->text() + " " + QString::fromStdString(user.getLogin()));
    ui->info_firstName->setText(ui->info_firstName->text() + " " + QString::fromStdString(user.getFirstName()));
    ui->info_lastName->setText(ui->info_lastName->text() + " " + QString::fromStdString(user.getLastName()));
    ui->info_mail->setText(ui->info_mail->text() + " " + QString::fromStdString(user.getEmail()));

    refreshPage();

}

void MainPage::on_button_deconnect_clicked()
{
    this->hide();
    ConnexionPage* connexionPage = new ConnexionPage();
    connexionPage->show();
}


void MainPage::on_button_create_database_clicked()
{

    DBCreatePage* dbCreatePage = new DBCreatePage();
    dbCreatePage->show();
    QDir databasePath;
    QString savePath = databasePath.currentPath()+"/MyDb.db";
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(savePath);
    database.open();
    qDebug() << "Base de donnée initialisée";

    QSqlQuery SqlQuery;
    SqlQuery.exec("create table test"
                  "(id integer primary key, "
                  "firstname varchar(20)");

}


void MainPage::on_button_search_database_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Database"), "/home", tr("Data Base Files (*.db)"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    db.open();

    QStringList nameList = db.tables();
    qDebug() << nameList;

    QSqlQuery* query = new QSqlQuery();
    query->prepare("select * from customers");
    query->exec();

    QSqlQueryModel * modal = new QSqlTableModel;
    modal->setQuery(std::move(*query));
    ui->tableView->setModel(modal);
    ui->tableView->show();

}


void MainPage::on_pushButton_clicked()
{
    NewProfile* profilePage = new NewProfile(this);
    connect(this, &MainPage::notifyUsernameProfile, profilePage, &NewProfile::onUsernameSent);
    connect(profilePage,SIGNAL(destroyed()),this,SLOT(refreshPage()));
    QString username = (ui->info_login->text()).mid(8);
    emit notifyUsernameProfile(username);
    profilePage->show();
}

void MainPage::refreshPage()
{
    QLayoutItem* item;
    while((item = ui->verticalLayout->takeAt(0)) != 0)
    {
        delete item->widget();
    }



    QDomNodeList profiles = XMLParser::getProfiles("myFile.xml",ui->info_login->text().mid(8));
    for (int i = 2 ; i < profiles.count() ; i++)
    {
        QLabel* newLabel = new QLabel(profiles.at(i).toElement().attribute("id", "not set"));
        newLabel->setStyleSheet("QLabel { color: white; }");

        Menu* enu = new Menu();
        newLabel->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(newLabel, SIGNAL(customContextMenuRequested(QPoint)), enu, SLOT(showMenu()));

        ui->verticalLayout->addWidget(newLabel);
    }
    qDebug() << "XML refreshed !";
}

