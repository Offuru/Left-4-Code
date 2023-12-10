#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_Name2PlayersWindow.h"
#include "Game.h"

class Name2PlayersWindow : public QMainWindow
{
	Q_OBJECT

public:
	Name2PlayersWindow(QWidget *parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~Name2PlayersWindow();

	void closeEvent(QCloseEvent* event);

public slots:
	void on_buttonBack_clicked();
	void on_gameModeButton_clicked();

private:
	Ui::Name2PlayersWindowClass ui;
	std::shared_ptr<twixt::Game> m_game;

	void setPlayersName();
};
