#pragma once

#include <QMainWindow>
#include <memory>

#include "ui_GameModeWindow.h"
#include "SettingsWindow.h"
#include "Game.h"

class GameModeWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameModeWindow(QWidget* parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~GameModeWindow();

	void closeEvent(QCloseEvent* event);

private slots:
	void openParentWindow();
	void openSettingsWindow();

private:
	std::unique_ptr<Ui::GameModeWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;
	std::unique_ptr<SettingsWindow> m_settingsWindow;
};
