#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
}

NameAIWindow::~NameAIWindow()
{}

void NameAIWindow::on_buttonBack_clicked()
{
	this->close();
	this->parentWidget()->show();
}