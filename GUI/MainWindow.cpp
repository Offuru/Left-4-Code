#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::MainWindowClass>() }
{
	m_game = std::make_shared<twixt::Game>();
	m_name2PlayersWindow = std::make_unique<Name2PlayersWindow>(this, m_game);
	m_nameAIWindow = std::make_unique<NameAIWindow>(this, m_game);
	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	m_ui->setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::on_twoPlayersButton_clicked()
{
	this->hide();
	m_game->setHumanPlayers(true);
	m_name2PlayersWindow->show();
}

void MainWindow::on_aiPlayerButton_clicked()
{
	this->hide();
	m_game->setHumanPlayers(false);
	m_nameAIWindow->show();
}