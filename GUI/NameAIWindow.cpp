#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::NameAIWindowClass>() }
{
	setWindowState(Qt::WindowMaximized);
	m_game = game;
	m_ui->setupUi(this);
	m_gameModeWindow = std::make_unique<GameModeWindow>(this, m_game);
	m_ui->setupUi(this);

	QObject::connect(m_ui->goBackButton, &QPushButton::clicked, this, &NameAIWindow::openParentWindow);
	QObject::connect(m_ui->gameModeButton, &QPushButton::clicked, this, &NameAIWindow::openGameModeWindow);
}

NameAIWindow::~NameAIWindow()
{}

void NameAIWindow::openParentWindow()
{
	this->hide();
	this->parentWidget()->show();
}

void NameAIWindow::openGameModeWindow()
{
	setPlayersName();
	if (!verifyPlayerName()) return;
	this->hide();
	m_gameModeWindow->show();
}

void NameAIWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}

void NameAIWindow::setPlayersName()
{
	std::string name1 = m_ui->player1NameLineEdit->text().toStdString();
	m_game->setPlayer1(name1);
	m_game->setPlayer2("Robot");
}

bool NameAIWindow::verifyPlayerName()
{
	std::regex nameRegex("[a-zA-Z]([a-z]*\d*)*");
	if (std::regex_match(m_game->getPlayer1()->getName(), nameRegex)) return true;
	return false;
}
