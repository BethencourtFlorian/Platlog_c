#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include "user.h"
#include "connexionpage.h"

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

private slots:
    /**
     * @brief Renvoie vers la page de connexion
     */
    void on_button_deconnect_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
