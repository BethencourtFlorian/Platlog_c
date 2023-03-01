#ifndef CONNEXIONPAGE_H
#define CONNEXIONPAGE_H

#include <QDialog>
#include "qdom.h"
#include <QFile>
#include "mainwindow.h"
#include "mainpage.h"
#include "user.h"
#include <QMainWindow>

namespace Ui {
class ConnexionPage;
}

class ConnexionPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConnexionPage(QWidget *parent = nullptr);
    ~ConnexionPage();

    /**
     * @brief Vérifie la combinaison login/mdp
     *
     * Ouvre la MainPage si elle existe dans le .xml.
     * Affiche une erreur sinon
     */
    void onConnectionButton_Click();

    /**
     * @brief Ouvre la fenêtre d'inscription
     */
    void onInscriptionButton_Click();

signals:
    /**
     * @brief Envoie les informations de l'utilisateur à la MainPage
     * @param user contient les informations de l'utilisateur
     */
    void notifyInfoSent(user& user);

private:
    Ui::ConnexionPage *ui;
};

#endif // CONNEXIONPAGE_H
