#ifndef NEWDATABASE_H
#define NEWDATABASE_H

#include <QWidget>

namespace Ui {
class NewDatabase;
}

class NewDatabase : public QWidget
{
    Q_OBJECT

public:
    explicit NewDatabase(QWidget *parent = nullptr);
    ~NewDatabase();

private:
    Ui::NewDatabase *ui;
};

#endif // NEWDATABASE_H
