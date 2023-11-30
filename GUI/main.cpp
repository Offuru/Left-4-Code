#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    twixt::Game test;
    test.Run();

    return a.exec();
}
