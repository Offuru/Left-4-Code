#include "GameModeWindow.h"

GameModeWindow::GameModeWindow(QWidget *parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;

	ui.setupUi(this);
}

GameModeWindow::~GameModeWindow()
{}

void GameModeWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}