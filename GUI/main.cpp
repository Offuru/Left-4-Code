#include "StartWindow.h"
#include <QtWidgets/QApplication>
#include "Game.h"

void addStyleToQApp(QApplication& app);

int main(int argc, char *argv[])
{
    QApplication TwixtApp(argc, argv);
    addStyleToQApp(TwixtApp);

    StartWindow window;
    window.show();

    return TwixtApp.exec();
}

void addStyleToQApp(QApplication& app)
{
    QFile file("Static files/QSS/styleSheet.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    app.setStyleSheet(styleSheet);
}