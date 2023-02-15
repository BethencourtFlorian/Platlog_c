#ifndef CONNEXIONPAGE_H
#define CONNEXIONPAGE_H

#include <QDialog>
#include "qdom.h"
#include <QFile>
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
    int onClick(void);

signals:
    void notifyInfoSent(user& user);

private:
    Ui::ConnexionPage *ui;
};

#endif // CONNEXIONPAGE_H
