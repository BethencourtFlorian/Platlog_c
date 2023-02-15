#include "headers/mainwindow.h"
#include "headers/connexionpage.h"

#include <QApplication>
#include <QtXml>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QFile::exists("myTestFilee.xml");
        MainWindow w;
        w.show();

    return a.exec();
}
