#include "mainwindow.h"
#include "signallib.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    SignalLib signalLib;
    w.show();
    return a.exec();
}
