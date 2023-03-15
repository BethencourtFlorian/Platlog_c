#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFileDialog>
#include "user.h"
#include "connexionpage.h"
#include "profile.h"
#include "database.h"
#include "XMLParser.h"
#include "menu.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QDialog
{
    Q_OBJECT
public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

public slots:
    void onInfoSent(User& user);
    void instanciatePage();
    void refreshPage();

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();

    void on_createUserButton_clicked();

private:
    Ui::AdminPage *ui;
    User user;
};

#endif // ADMINPAGE_H
