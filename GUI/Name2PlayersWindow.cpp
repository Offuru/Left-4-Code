#include "Name2PlayersWindow.h"

Name2PlayersWindow::Name2PlayersWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{std::make_unique<Ui::Name2PlayersWindowClass>()}
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	m_gameModeWindow = std::make_unique<GameModeWindow>(this, m_game);
	m_ui->setupUi(this);
}

Name2PlayersWindow::~Name2PlayersWindow()
{}

void Name2PlayersWindow::on_goBackButton_clicked()
{
	this->hide();
	this->parentWidget()->show();
}

void Name2PlayersWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}

void Name2PlayersWindow::on_gameModeButton_clicked()
{
	setPlayersName();
	this->hide();
	m_gameModeWindow->show();
}

void Name2PlayersWindow::setPlayersName()
{
	std::string name1 = m_ui->player1NameLineEdit->text().toStdString();
	std::string name2 = m_ui->player2NameLineEdit->text().toStdString();
	m_game->setPlayer1(name1);
	m_game->setPlayer2(name2);
	m_game->getPlayer2()->setColor(twixt::Pylon::Color::Black);
}
