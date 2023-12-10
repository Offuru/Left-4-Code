#include "Name2PlayersWindow.h"

Name2PlayersWindow::Name2PlayersWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window |Qt::MSWindowsFixedSizeDialogHint);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
}

Name2PlayersWindow::~Name2PlayersWindow()
{}

void Name2PlayersWindow::on_buttonBack_clicked()
{
	this->close();
	this->parentWidget()->show();
}