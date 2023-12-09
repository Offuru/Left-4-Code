#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_name2PlayersWindow = std::make_unique<Name2PlayersWindow>();
    m_nameAIWindow = std::make_unique<NameAIWindow>();
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::on_button2Players_clicked()
{
    this->close();
    m_name2PlayersWindow->show();
}

void MainWindow::on_buttonAIPlayer_clicked()
{
    this->close();
    m_nameAIWindow->show();
}