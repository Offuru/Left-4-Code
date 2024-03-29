#include "StartWindow.h"

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::StartWindowClass>() }
{
	m_game = std::make_shared<twixt::Game>();
	m_name2PlayersWindow = std::make_unique<Name2PlayersWindow>(this, m_game);
	setWindowState(Qt::WindowMaximized);
	m_ui->setupUi(this);

	QObject::connect(m_ui->playButton, &QPushButton::clicked, this, &StartWindow::openTwoPlayersWindow);
}

StartWindow::~StartWindow()
{}

void StartWindow::openTwoPlayersWindow()
{
	this->hide();
	m_game->setHumanPlayers(true);
	m_name2PlayersWindow->show();
}