#ifndef MENU_H
#define MENU_H

#include <QMenu>
#include <QCursor>


class Menu : public QMenu
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);

signals:

public slots:
    void showMenu();
};

#endif // MENU_H
