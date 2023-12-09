#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    //test.Run();

    return a.exec();
}
