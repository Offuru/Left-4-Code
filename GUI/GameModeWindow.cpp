#include "GameModeWindow.h"

GameModeWindow::GameModeWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::GameModeWindowClass>() }
{
	setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
	m_game = game;

	m_ui->setupUi(this);
}

GameModeWindow::~GameModeWindow()
{}

void GameModeWindow::on_backButton_clicked()
{
	this->hide();
	this->parentWidget()->show();
}

void GameModeWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}