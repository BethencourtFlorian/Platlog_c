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

void MainPage::onInfoSent(User& sentUser)
{
    user = sentUser;
    // Chaque champ de la vue est remplie avec les informations de l'utilisateur récupérées par la vue Connexion
    ui->title->setText(user.getFirstName() + "'s " + ui->title->text());
    ui->info_login->setText(ui->info_login->text() + " " + user.getLogin());
    ui->info_firstName->setText(ui->info_firstName->text() + " " + user.getFirstName());
    ui->info_lastName->setText(ui->info_lastName->text() + " " + user.getLastName());
    ui->info_mail->setText(ui->info_mail->text() + " " + user.getEmail());

    refreshPage();
}

void MainPage::on_button_deconnect_clicked()
{
    this->hide();
    ConnexionPage* connexionPage = new ConnexionPage();
    connexionPage->show();
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
    Profile* profilePage = new Profile(this);
    connect(this, &MainPage::notifyLoginProfile, profilePage, &Profile::onLoginSent);
    connect(profilePage,SIGNAL(destroyed()),this,SLOT(refreshPage()));
    QString login = (ui->info_login->text()).mid(8);
    emit notifyLoginProfile(login);
    profilePage->show();
}

void MainPage::refreshPage()
{
    QLayout* layout = ui->verticalLayout;
    QLayoutItem* item;
    while((item = layout->takeAt(0)) != 0)
    {
        if(item->widget() != 0)
            delete item->widget();
        delete item;
    }

    XMLParser::fillUser("myFile.xml", user);
    list<Profile*> listProfiles = user.getProfiles();
    for(auto it = listProfiles.begin(); it != listProfiles.end(); it++){
        QLabel* newLabel = new QLabel((*it)->getId());
        newLabel->setStyleSheet("QLabel { color: white; }");

        Menu* menu = new Menu();
        newLabel->setContextMenuPolicy(Qt::CustomContextMenu);
        connect(newLabel, SIGNAL(customContextMenuRequested(QPoint)), menu, SLOT(showMenu()));

        ui->verticalLayout->addWidget(newLabel);
    }
}

