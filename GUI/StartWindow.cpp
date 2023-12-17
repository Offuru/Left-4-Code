#include "StartWindow.h"

StartWindow::StartWindow(QWidget* parent)
	: QMainWindow(parent), m_ui{ std::make_unique<Ui::StartWindowClass>() }
{
	m_game = std::make_shared<twixt::Game>();
	m_name2PlayersWindow = std::make_unique<Name2PlayersWindow>(this, m_game);
	m_nameAIWindow = std::make_unique<NameAIWindow>(this, m_game);
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	m_ui->setupUi(this);
}

StartWindow::~StartWindow()
{}

void StartWindow::on_twoPlayersButton_clicked()
{
	this->hide();
	m_game->setHumanPlayers(true);
	m_name2PlayersWindow->show();
}

void StartWindow::on_aiPlayerButton_clicked()
{
	this->hide();
	m_game->setHumanPlayers(false);
	m_nameAIWindow->show();
}