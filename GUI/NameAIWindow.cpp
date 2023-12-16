#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	ui.setupUi(this);
}

NameAIWindow::~NameAIWindow()
{
	this->close();
}

void NameAIWindow::on_backButton_clicked()
{
	this->hide();
	this->parentWidget()->show();
}

void NameAIWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}