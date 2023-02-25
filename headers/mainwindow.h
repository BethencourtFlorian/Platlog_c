#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QCryptographicHash.h>
#include "connexionpage.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Incrit le nouvel utilisateur dans le fichier XML.
     */
    void storage();

private:
    Ui::MainWindow *ui;

    QString login;
    QString password;
    QString email;
    QString firstName;
    QString lastName;
};
#endif // MAINWINDOW_H
