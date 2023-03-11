#ifndef PROFILE_H
#define PROFILE_H

#include <QDomDocument>
#include <QFile>
#include <QObject>
#include "qdialog.h"
#include "user.h"
#include "mainpage.h"

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    ~Profile();

public slots:
    void onLoginSent(QString& login);


private slots:
    void on_createProfile_clicked();

signals:
    void destroyed();

private:
    Ui::Profile *ui;
    QString id;
    QString loginUser;
};

#endif // PROFILE_H
