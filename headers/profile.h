#ifndef PROFILE_H
#define PROFILE_H

#include <list>
#include <QDomDocument>
#include <QFile>
#include <QObject>
#include <QDialog>
#include "database.h"

namespace Ui {
class Profile;
}

class Profile : public QDialog
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = nullptr);
    Profile(const Profile&);
    Profile(QString id, QString loginUser);
    ~Profile();

    Profile &operator=(const Profile& source);

    void addDb(Database* db);

    QString getId() const;
    void setId(const QString &newId);
    QString getLoginUser() const;
    void setLoginUser(const QString &newLoginUser);

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
    std::list<Database*> databases;
};

#endif // PROFILE_H
