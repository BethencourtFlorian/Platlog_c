#ifndef DATABASEADD_H
#define DATABASEADD_H

#include <QWidget>
#include <QFileDialog>
#include "user.h"
#include "XMLParser.h"

namespace Ui {
class DatabaseAdd;
}

class DatabaseAdd : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseAdd(QWidget *parent = nullptr);
    ~DatabaseAdd();

public slots:
    void onUserSent(User& user);
    void onUserWithSelectedSent(User& user, QString selectedItem);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void destroyedDB(unsigned int idProfile);

private:
    Ui::DatabaseAdd *ui;
    User user;
};

#endif // DATABASEADD_H
