#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QFileDialog>
#include <QTreeWidgetItem>
#include <QStandardItemModel>
#include <QStandardItem>
#include "user.h"
#include "connexionpage.h"
#include "profile.h"
#include "database.h"
#include "XMLParser.h"
#include "menu.h"
#include "comboboxdelegate.h"

namespace Ui {
class AdminPage;
}

class AdminPage : public QDialog
{
    Q_OBJECT
public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

    User* getUserWithLogin(QString login);

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

    void onTreeNode_Clicked(QTreeWidgetItem *item, int column);

private:
    Ui::AdminPage *ui;
    User user;
    list<User*> listUsers;
};

#endif // ADMINPAGE_H
