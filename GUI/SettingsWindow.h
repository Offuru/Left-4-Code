#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_SettingsWindow.h"
#include "Game.h"

class SettingsWindow : public QMainWindow
{
	Q_OBJECT

public:
	SettingsWindow(QWidget *parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~SettingsWindow();

	void enableMineGameModeSettings();
	void enableBigPylonsGameModeSettings();

private slots:
	void setNoSquarePylons();
	void setNoCrossPylons();

private:
	std::unique_ptr<Ui::SettingsWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;
};
