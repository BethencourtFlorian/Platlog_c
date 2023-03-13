#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QDialog>

namespace Ui {
class Database;
}

class Database : public QDialog
{
    Q_OBJECT

public:
    explicit Database(QWidget *parent = nullptr);
    Database(QString newName, QString newPath);
    Database(const Database& source);
    Database &operator=(const Database& source);

    ~Database();

    QString getName() const;
    QString getPath() const;
    void setName(const QString &newName);
    void setPath(const QString &newPath);

private:
    Ui::Database *ui;
    QString name;
    QString path;

};

#endif // DATABASE_H
