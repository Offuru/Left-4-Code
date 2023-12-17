#include "SettingsWindow.h"

SettingsWindow::SettingsWindow(QWidget *parent)
	: QMainWindow{ parent }, m_ui{ std::make_unique<Ui::SettingsWindowClass>() }
{
	m_ui->setupUi(this);
}

SettingsWindow::~SettingsWindow()
{}
