#include "GameWindow.h"

GameWindow::GameWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::GameWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

	m_game = game;

	m_ui->setupUi(this);
}

GameWindow::~GameWindow()
{}

void GameWindow::closeEvent(QCloseEvent * event)
{
	QCoreApplication::quit();
}
