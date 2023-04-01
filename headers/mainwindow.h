#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QCryptographicHash.h>
#include "connexionpage.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int XML = 1, QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief closeWindow
     *
     * Ferme la fenêtre d'inscription et ouvre celle de la connexion
     */
    void closeWindow();

    /**
     * @brief Incrit le nouvel utilisateur dans le fichier XML.
     */
    void storage();

signals:
    void notifyCloseSignup(User* user);

private:
    Ui::MainWindow *ui;

    QString login;
    QString password;
    QString email;
    QString firstName;
    QString lastName;

    int XML;
};
#endif // MAINWINDOW_H
