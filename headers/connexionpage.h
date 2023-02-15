#ifndef CONNEXIONPAGE_H
#define CONNEXIONPAGE_H

#include <QDialog>
#include "qdom.h"
#include <QFile>
#include "../src/mainpage.h"

namespace Ui {
class ConnexionPage;
}

class ConnexionPage : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionPage(QWidget *parent = nullptr);
    ~ConnexionPage();
    int onClick(void);

signals:
    void notifyInfoSent(const QString& name);

private:
    Ui::ConnexionPage *ui;
};

#endif // CONNEXIONPAGE_H
