#include "Name2PlayersWindow.h"

Name2PlayersWindow::Name2PlayersWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
}

Name2PlayersWindow::~Name2PlayersWindow()
{}

void Name2PlayersWindow::on_buttonBack_clicked()
{
	this->hide();
	this->parentWidget()->show();
}

void Name2PlayersWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}