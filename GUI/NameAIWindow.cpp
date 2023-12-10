#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
}

NameAIWindow::~NameAIWindow()
{
	this->close();
}

void NameAIWindow::on_buttonBack_clicked()
{
	this->hide();
	this->parentWidget()->show();
}

void NameAIWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}