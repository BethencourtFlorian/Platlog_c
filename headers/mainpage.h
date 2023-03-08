#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFileDialog>
#include "user.h"
#include "connexionpage.h"
#include "dbcreatepage.h"
#include "newprofile.h"
#include "XMLParser.h"
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
    void onInfoSent(user& user);
    void refreshPage();


private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();


    void on_button_create_database_clicked();

    void on_button_search_database_clicked();

    void on_pushButton_clicked();

signals:
    void notifyUsernameProfile(QString& username);

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
