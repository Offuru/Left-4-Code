#include "GameModeWindow.h"
#include <iostream>

GameModeWindow::GameModeWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::GameModeWindowClass>() }
{
	setWindowState(Qt::WindowMaximized);
	m_game = game;
	m_settingsWindow = std::make_unique<SettingsWindow>(this, m_game);
	m_gameWindow = std::make_unique<GameWindow>(this, m_game);

	m_ui->setupUi(this);

	QObject::connect(m_ui->backButton, &QPushButton::clicked, this, &GameModeWindow::openParentWindow);
	QObject::connect(m_ui->settingsButton, &QPushButton::clicked, this, &GameModeWindow::openSettingsWindow);
	QObject::connect(m_ui->startButton, &QPushButton::clicked, this, &GameModeWindow::openGameWindow);

	QObject::connect(m_ui->bigPylonsGMButton, &QPushButton::clicked,
					[&]() { m_game->setBigPylons(true); m_settingsWindow->enableBigPylonsGameModeSettings(); m_ui->bigPylonsGMButton->setStyleSheet("background-color: #6A6B83;");});

	QObject::connect(m_ui->mineGMButton, &QPushButton::clicked, this, &GameModeWindow::setupMineGameMode);

	QObject::connect(m_ui->debuilderGMButton, &QPushButton::clicked, this, &GameModeWindow::debuilderGameModeButtonAction);

	QObject::connect(m_ui->cardsGMButton, &QPushButton::clicked,
					[&]() { m_game->setCards(true); m_ui->cardsGMButton->setStyleSheet("background-color: #6A6B83;"); });
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
	m_settingsWindow->setWindowModality(Qt::ApplicationModal);
	m_settingsWindow->show();
}

void GameModeWindow::openGameWindow()
{
	m_game->setCurrentPlayer(nonstd::make_observer<twixt::IPlayer>(m_game->getPlayer1().get()));
	m_gameWindow->setFoundationsPoints(std::vector<QPoint>(pow(m_game.get()->getBoard().getSize(), 2)));
	m_gameWindow->changeVisibilityBigPylonsButtons(m_game->getBigPylons());
	m_gameWindow->changeVisibilityCards(m_game->getCards());
	m_gameWindow->setPlayersNameLabel();
	m_gameWindow->updateNumberPylonsPlayersLabel(); 
	m_gameWindow->resetPushButtonIcon();
	m_gameWindow->scaleImages();
	if (m_game->getDebuilderBob()) m_game->moveBob();
	if (m_game->getCards()) m_game->addCardsToDeck();
	if (m_game->getMinedFoundations()) m_game->getBoard().spawnMines();
	this->hide();
	m_gameWindow->show();
}

void GameModeWindow::setupMineGameMode()
{
	m_ui->mineGMButton->setStyleSheet("background-color: #6A6B83;");
	m_game->setMinedFoundations(true);
	m_settingsWindow->enableMineGameModeSettings();
}

void GameModeWindow::debuilderGameModeButtonAction()
{
	m_game->setDebuilderBob(true); 
	m_ui->debuilderGMButton->setStyleSheet("background-color: #6A6B83;");
	m_ui->debuilderImageLabel->setPixmap(QPixmap("Static files/Images/Game modes images/Bob The Debuilder.png"));
}

void GameModeWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}