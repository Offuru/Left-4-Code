#include "NameAIWindow.h"

NameAIWindow::NameAIWindow(QWidget* parent, std::shared_ptr<twixt::Game> game)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::NameAIWindowClass>() }
{
	setWindowState(Qt::WindowMaximized);
	m_game = game;
	m_ui->setupUi(this);

	QObject::connect(m_ui->goBackButton, &QPushButton::clicked, this, &NameAIWindow::openParentWindow);
}

NameAIWindow::~NameAIWindow()
{}

void NameAIWindow::openParentWindow()
{
	this->hide();
	this->parentWidget()->show();
}

void NameAIWindow::closeEvent(QCloseEvent* event)
{
	QCoreApplication::quit();
}