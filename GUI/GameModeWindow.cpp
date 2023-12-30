#include "GameModeWindow.h"
#include <iostream>

GameModeWindow::GameModeWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::GameModeWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	m_settingsWindow = std::make_unique<SettingsWindow>(this, m_game);
	m_gameWindow = std::make_unique<GameWindow>(this, m_game);

	m_ui->setupUi(this);

	QObject::connect(m_ui->backButton, &QPushButton::clicked, this, &GameModeWindow::openParentWindow);
	QObject::connect(m_ui->settingsButton, &QPushButton::clicked, this, &GameModeWindow::openSettingsWindow);
	QObject::connect(m_ui->startButton, &QPushButton::clicked, this, &GameModeWindow::openGameWindow);

	QObject::connect(m_ui->bigPylonsGMButton, &QPushButton::clicked,
					[&]() { m_game->setBigPylons(true); });

	QObject::connect(m_ui->mineGMButton, &QPushButton::clicked,
					[&]() { m_game->setMinedFoundations(true); });

	QObject::connect(m_ui->debuilderGMButton, &QPushButton::clicked,
					[&]() { m_game->setDebuilderBob(true); });

	QObject::connect(m_ui->cardsGMButton, &QPushButton::clicked,
					[&]() { m_game->setCards(true); });
}

GameModeWindow::~GameModeWindow()
{}

void GameModeWindow::openParentWindow()
{
	this->hide();
	this->parentWidget()->show();
}

void GameModeWindow::openSettingsWindow()
{
	m_settingsWindow->show();
}

void GameModeWindow::openGameWindow()
{
	this->hide();
	m_gameWindow->show();
}

void GameModeWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}