#include "headers/mainwindow.h"
#include "headers/connexionpage.h"
#include <QFile>
#include <QApplication>
#include <QtXml>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow w;
        ConnexionPage c;

        if (QFile::exists("userInfo.xml"))
            c.show();
        else
            w.show();
    return a.exec();
}
