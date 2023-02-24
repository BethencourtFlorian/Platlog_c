#include "headers/mainwindow.h"
#include "headers/connexionpage.h"
#include <QFile>
#include <QApplication>
#include <QtXml>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        MainWindow w; // Page "par défaut", c'est-à-dire l'inscription
        ConnexionPage c;

        if (QFile::exists("myFile.xml"))
            c.show();
        else
            w.show();
    return a.exec();
}
