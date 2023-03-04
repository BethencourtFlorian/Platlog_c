#ifndef NEWPROFILE_H
#define NEWPROFILE_H

#include <QDomDocument>
#include <QFile>
#include <QObject>
#include "qdialog.h"
#include "user.h"
#include "mainpage.h"

namespace Ui {
class NewProfile;
}

class NewProfile : public QDialog
{
    Q_OBJECT

public:
    explicit NewProfile(QWidget *parent = nullptr);
    ~NewProfile();

public slots:
    void onUsernameSent(QString& username);


private slots:
    void on_createProfile_clicked();

signals:
    void destroyed();

private:
    Ui::NewProfile *ui;
    QString username;
};

#endif // NEWPROFILE_H
