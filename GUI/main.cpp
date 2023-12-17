#include "StartWindow.h"
#include <QtWidgets/QApplication>
#include "Game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWindow w;
    //w.setWindowState(Qt::WindowMaximized);
    w.show();
    //test.Run();

    return a.exec();
}
