#pragma once

#include <QMainWindow>
#include <memory>
#include "ui_NameAIWindow.h"
#include "Game.h"

class NameAIWindow : public QMainWindow
{
	Q_OBJECT

public:
	NameAIWindow(QWidget* parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~NameAIWindow();

	void closeEvent(QCloseEvent* event);

public slots:
	void on_buttonBack_clicked();

private:
	Ui::NameAIWindowClass ui;
	std::shared_ptr<twixt::Game> m_game;
};
