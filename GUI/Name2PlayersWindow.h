#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_Name2PlayersWindow.h"
#include "Game.h"
#include "GameModeWindow.h"

class Name2PlayersWindow : public QMainWindow
{
	Q_OBJECT

public:
	Name2PlayersWindow(QWidget* parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~Name2PlayersWindow();

	void closeEvent(QCloseEvent* event);

private slots:
	void openParentWindow();
	void openGameModeWindow();

private:
	std::unique_ptr<Ui::Name2PlayersWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;
	std::unique_ptr<GameModeWindow> m_gameModeWindow;

	void setPlayersName();
};
