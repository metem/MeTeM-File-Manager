/*
*           Copyright 2012 by Mateusz Ucher
*
*              GNU GENERAL PUBLIC LICENSE
*                Version 3, 29 June 2007
*/

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool log = false;
    for (int i = 1; i < argc; i++) log = log | (QString(argv[i]) == "-l");

    MainWindow w(log);
    w.show();

    return a.exec();
}
