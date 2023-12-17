#pragma once

#include <QtWidgets/QMainWindow>
#include <memory>

#include "ui_MainWindow.h"
#include "Name2PlayersWindow.h"
#include "NameAIWindow.h"
#include "Game.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();

public slots:
	void on_twoPlayersButton_clicked();
	void on_aiPlayerButton_clicked();

private:
	std::unique_ptr<Ui::MainWindowClass> m_ui;
	std::unique_ptr<Name2PlayersWindow> m_name2PlayersWindow;
	std::unique_ptr<NameAIWindow> m_nameAIWindow;
	std::shared_ptr<twixt::Game> m_game;
};
