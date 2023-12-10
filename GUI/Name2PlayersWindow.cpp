#include "Name2PlayersWindow.h"

Name2PlayersWindow::Name2PlayersWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow(parent)
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;
	ui.setupUi(this);
}

Name2PlayersWindow::~Name2PlayersWindow()
{}

void Name2PlayersWindow::on_buttonBack_clicked()
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
}

void Name2PlayersWindow::setPlayersName()
{
	std::string name1 = ui.player1NameLineEdit->text().toStdString();
	std::string name2 = ui.player2NameLineEdit->text().toStdString();
	m_game->setPlayer1({ name1 });
	m_game->setPlayer2({ name2 });
	m_game->getPlayer2().setColor(twixt::Pylon::Color::Black);
}
