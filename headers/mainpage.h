#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QDialog>
#include "user.h"
#include "connexionPage.h"

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
    void onInfoSent(user &);

private slots:
    void on_button_deconnect_clicked();

private:
    Ui::MainPage *ui;
};

#endif // MAINPAGE_H
