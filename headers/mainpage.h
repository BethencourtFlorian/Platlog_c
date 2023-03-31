#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include "user.h"
#include "connexionpage.h"
#include "profile.h"
#include "XMLParser.h"
#include "databaseadd.h"
#include "menu.h"

namespace Ui {
class MainPage;
}

class MainPage : public QDialog
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();

public slots:
    /**
     * @brief Remplit la MainPage
     *
     * Avec les informations de l'utilisateur passé en paramètre
     * @param user contient les informations de l'utilisateur
     */
    void onInfoSent(User& user);
    void instanciatePage();
    void refreshProfile();
    void refreshDB(unsigned int idProfile);

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_pushButton_3_clicked();

signals:
    void notifyUsernameProfile(QString& username);
    void notifyUser(User& user);
    void notifyUserWithSelected(User& user, QString selectedItem);

private:
    Ui::MainPage *ui;
    User user;
};

#endif // MAINPAGE_H
