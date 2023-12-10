#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	ui.setupUi(this);
}

NameAIWindow::~NameAIWindow()
{}
