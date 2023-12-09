#include "Name2PlayersWindow.h"

Name2PlayersWindow::Name2PlayersWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
}

Name2PlayersWindow::~Name2PlayersWindow()
{}
