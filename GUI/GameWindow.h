#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QBrush>
#include <QFileDialog>
#include <QMouseEvent>

#include <functional>
#include <memory>

#include "EndDialog.h"
#include "ui_GameWindow.h"
//#include "GameLoader.h"
#include "Game.h"
#include "CardQListWidgetItem.h"

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	enum class Action
	{
		None,
		Add_SinglePylon,
		Add_SquarePylonConfig1,
		Add_SquarePylonConfig2,
		Add_CrossPylonConfig1,
		Add_CrossPylonConfig2, 
		Add_Mine,
		Add_Bridge,
		Remove_Bridge
	};

	GameWindow(QWidget* parent = nullptr, std::shared_ptr<twixt::Game> game = nullptr);
	~GameWindow();

	void setFoundationsPoints(const std::vector<QPoint>& foundationsPoints);
	void setPlayersNameLabel();
	void updateNumberPylonsPlayersLabel();

	void closeEvent(QCloseEvent* event);
	void changeVisibilityBigPylonsButtons(bool state);
	void changeVisibilityCards(bool state);

private slots:
	void swapButtonAction();
	void nextRoundAction();
	void saveGameAction();
	void loadGameAction();
	void drawCardAction();
	void useCardAction(QListWidgetItem* item);

private:
	std::vector<QPoint> m_foundationsPoints;

	std::unique_ptr<EndDialog> m_endDialog;
	std::unique_ptr<Ui::GameWindowClass> m_ui;
	std::shared_ptr<twixt::Game> m_game;

	Action m_currentAction;
	twixt::Position m_currentBridgeStartPos;
	twixt::Game::GameStatus m_currentStatus;
	Card::Effect m_currentEffect;
	int m_pylonRotation;
	bool m_pylonPlaced;
	bool m_cardDrawn;
	bool m_cardUsed;
	bool m_gameEnded;

	nonstd::observer_ptr<twixt::IPlayer> m_currentPlayer;

	void addPylon(const twixt::Position& matPosition);
	void addBridge(const twixt::Position& endPosition);
	void removeBridge(const twixt::Position& endPosition);
	void drawBoard(QPainter* painter);
	void drawBoardLines(QPainter* painter);
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;

	void rotatePushButtonIcon(QPushButton& button, int rotationFactor);
	void resetPushButtonIcon();
	QPoint matCoordToQPoint(const twixt::Position& pos);
	twixt::Position qPointToMatCoord(const QPoint& pos);
	QRect makeSquareBoardSize();
};
