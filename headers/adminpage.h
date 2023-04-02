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

    /**
     * @brief Retrouve un utilisateur en fonction de son login
     * @param login login de l'utilisateur
     * @return User* objet utilisateur
     */
    User* getUserWithLogin(QString login);

    /**
     * @brief Retrouve un profil en fonction de son id
     * @param id id de correspondant au profil
     * @param user utilisateur possédant le profil
     * @return Profile* objet profil
     */
    Profile* getProfileWithId(QString id, User* user);

    /**
     * @brief Retrouve une base de données en fonction de son nom
     * @param name nom de la base de données
     * @param profile profil auquel la base de données est rattachée
     * @return Database* objet database
     */
    Database* getDatabaseWithName(QString name, Profile* profile);

    /**
     * @brief Remplit la table d'affichage des utilisateurs en fonction des utilisateurs créés
     * @param user utilisateur à ajouter
     */
    void fillTableWithUser(User* user);

    /**
     * @brief Remplit la table d'affichage des profils en fonction des profils créés
     * @param profile profil à ajouter
     */
    void fillTableWithProfile(Profile* profile);

    /**
     * @brief Remplit la table d'affichage des bases de données en fonction des bases créés
     * @param database base de données à ajouter
     */
    void fillTableWithDatabase(Database* database);

public slots:

    /**
     * @brief Gère la réception de l'objet utilisateur
     * @param user utilisateur reçu
     */
    void onInfoSent(User& user);

    /**
     * @brief instancie la page en fonction des objets créés
     */
    void instanciatePage();

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();

    /**
     * @brief Gère la création d'un utilisateur
     */
    void on_createUserButton_clicked();

    /**
     * @brief Gère l'ajout d'un profil
     */
    void on_addProfileButton_clicked();

    /**
     * @brief Gère l'ajout d'une base de données
     */
    void on_addDatabaseButton_clicked();

    /**
     * @brief Gère la sauvegarde des informations entrées
     */
    void on_saveButton_clicked();

    /**
     * @brief Gère la suppression d'un élément
     */
    void on_deleteButton_clicked();

    /**
     * @brief Gère le click d'un élément du TreeNode
     * @param item item sélectionné
     * @param column colonne sélectionnée (toujours égal à 0)
     */
    void onTreeNode_Clicked(QTreeWidgetItem *item, int column);

    /**
     * @brief Gère la modification d'un utilisateur
     * @param item item sélectionné
     */
    void onUserChanged(QStandardItem* item);

    /**
     * @brief Gère la modification d'un profil
     * @param item item sélectionné
     */
    void onProfileChanged(QStandardItem* item);

    /**
     * @brief Gère la modification d'une base de données
     * @param item item sélectionné
     */
    void onDatabaseChanged(QStandardItem* item);

    /**
     * @brief Appelle la fenêtre de recherche d'une base de données pour un élément
     * @param index index du profil
     */
    void openFileDialog(const QModelIndex& index);

    /**
     * @brief Ajoute un nouvel utilisateur dans l'arbre
     * @param user utilisateur à ajouter
     */
    void addUserTree(User* user);

    /**
     * @brief Ajoute un nouveau profil dans l'arbre
     * @param id id du profil à ajouter
     */
    void addProfileTree(QString id);

    /**
     * @brief Ajoute une nouvelle base de données dans l'arbre
     * @param dabatase objet base de données à ajouter
     */
    void addDatabaseTree(Database* database);

private:
    Ui::AdminPage *ui;
    User user;
    list<User*> listUsers;
};

#endif // ADMINPAGE_H
