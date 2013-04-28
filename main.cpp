#include "mainwindow.h"
#include "finderdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
 //   MainWindow w;
 //   w.show();

    FinderDialog fd("/media/D/temp/", true);
    fd.show();

    return a.exec();
}
