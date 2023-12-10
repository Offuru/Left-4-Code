#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    ui.setupUi(this);
}

MainWindow::~MainWindow()
{}

void MainWindow::on_button2Players_clicked()
{
    m_name2PlayersWindow = std::make_unique<Name2PlayersWindow>(this);
    this->close();
    m_name2PlayersWindow->show();
}

void MainWindow::on_buttonAIPlayer_clicked()
{
    m_nameAIWindow = std::make_unique<NameAIWindow>(this);
    this->close();
    m_nameAIWindow->show();
}