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
#include "database.h"
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

    /**
     * @brief Instancie le treeview avec le contenu du fichier XML
     */
    void instanciatePage();

    /**
     * @brief Ajoute un nouveau profil dans le treeView
     */
    void refreshProfile();

    /**
     * @brief Ajoute une nouvelle base de données dans un treeView
     */
    void refreshDB(unsigned int idProfile);

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();

    /**
     * @brief Renvoie vers la page de création d'utilisateur (pré-remplie)
     */
    void on_button_update_clicked();

    /**
     * @brief Renvoie vers la page d'ajout d'un profil
     */
    void on_pushButton_clicked();

    /**
     * @brief Renvoie vers la page d'ajout d'une base de données
     */
    void on_pushButton_2_clicked();

    /**
     * @brief Gère la suppression d'un profil/base de données
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Listener du click sur un élément du treeView
     * @param item item du TreeWidget cliqué
     * @param column colonne à manipuler (toujours 0)
     */
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    /**
     * @brief Listener du double click sur un élément du treeView
     * @param item item du TreeWidget double cliqué
     * @param column colonne à manipuler (toujours 0)
     */
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    /**
     * @brief Listener de la modification du User via la page d'inscription
     * @param userUpdated utilisateur contenant les nouvelles informations
     */
    void editInfoUser(User userUpdated);

signals:

    /**
     * @brief signal transférant le nom d'un profil d'une page à l'autre
     * @param username pseudo du profil à transférer
     */
    void notifyUsernameProfile(QString& username);

    /**
     * @brief signal transférant une base de données d'une page à l'autre
     * @param db objet base de données à transférer
     */
    void notifyDbSent(QSqlDatabase& db);

    /**
     * @brief signal transférant un utilisateur d'une page à l'autre
     * @param user utilisateur à transférer
     */
    void notifyUser(User& user);

    /**
     * @brief signal transférant un utilisateur ainsi que le profil sélectionné sur la TreeView
     * @param user utilisateur à transférer
     * @param selectedItem nom du profil sélectionné dans la TreeView
     */
    void notifyUserWithSelected(User& user, QString selectedItem);

    /**
     * @brief signal transférant un utilisateur à la page d'inscription pour mettre à jour ses informations
     * @param user utilisateur à transférer
     */
    void notifyUserEdit(User user);

private:
    Ui::MainPage *ui;
    User user;
};

#endif // MAINPAGE_H
