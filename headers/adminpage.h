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
#include <QMessageBox>
#include "user.h"
#include "connexionpage.h"
#include "profile.h"
#include "database.h"
#include "XMLParser.h"
#include "menu.h"
#include "comboboxdelegate.h"
#include "mainwindow.h"

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
    Profile* getProfileWithId(QString id, User* user);
    Database* getDatabaseWithName(QString name, Profile* profile);

    void fillTableWithUser(User* user);
    void fillTableWithProfile(Profile* profile);
    void fillTableWithDatabase(Database* database);

public slots:
    void onInfoSent(User& user);
    void instanciatePage();

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();

    void on_createUserButton_clicked();
    void on_addProfileButton_clicked();
    void on_addDatabaseButton_clicked();
    void on_saveButton_clicked();
    void on_deleteButton_clicked();

    void onTreeNode_Clicked(QTreeWidgetItem *item, int column);
    void onUserChanged(QStandardItem* item);
    void onProfileChanged(QStandardItem* item);
    void onDatabaseChanged(QStandardItem* item);
    void openFileDialog(const QModelIndex& index);
    void addUserTree(User* user);
    void addProfileTree(QString id);
    void addDatabaseTree(Database* database);

private:
    Ui::AdminPage *ui;
    User user;
    list<User*> listUsers;
};

#endif // ADMINPAGE_H
