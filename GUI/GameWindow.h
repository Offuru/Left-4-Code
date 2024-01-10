#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QBrush>
#include <QMouseEvent>
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

	void setFoundationsPoints(std::vector<QPoint> foundationsPoints);

	void closeEvent(QCloseEvent* event);
	void changeVisibilityBigPylonsButtons(bool state);

private:
	std::vector<QPoint> m_foundationsPoints;

	std::unique_ptr<Ui::GameWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;

	void drawBoard(QPainter* painter);
	void drawBoardLines(QPainter* painter);
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

	QPoint matCoordToQPoint(twixt::Position pos);
	twixt::Position qPointToMatCoord(QPoint pos);
	QRect makeSquareBoardSize();
};
