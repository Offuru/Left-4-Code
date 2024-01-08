#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QBrush>
#include <functional>
#include <memory>

#include "ui_GameWindow.h"
#include "Game.h"

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(QWidget* parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~GameWindow();

	void closeEvent(QCloseEvent* event);

private:
	std::unique_ptr<Ui::GameWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;

	void drawBoard(QPainter* painter);
	void drawBoardLines(QPainter* painter);
	void paintEvent(QPaintEvent* event) override;

	QPoint matCoordToQPoint(twixt::Position pos);
};
