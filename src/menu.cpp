#include "headers/menu.h"

Menu::Menu(QWidget *parent) : QMenu(parent)
{
    addAction("Add Database");
}

void Menu::showMenu()
{
    exec(QCursor::pos());
}
