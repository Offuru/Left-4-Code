#pragma once
#include "Board.h"
#include "Player.h"
#include "DebuilderBob.h"
#include <array>
#include <iostream>

class Game
{
public:

	Game();
	Game(const Game&);
	Game& operator=(const Game&);
	~Game() = default;

	void setBigPylons(bool);
	void setMinedFoundations(bool);
	void setReusableMinedFoundation(bool);
	void setDebuilderBob(bool);
	void setCards(bool);
	void setPlayer1(const Player&);
	void setPlayer2(const Player&);
	void setBoard(const Board&);

	bool getBigPylons() const;
	bool getMinedFoundations() const;
	bool getReusableMinedFoundation() const;
	bool getDebuilderBob() const;
	bool getCards() const;
	Player getPlayer1() const;
	Player getPlayer2() const;
	Board& getBoard();

	bool addPylon(const Position&, Pylon::Type, Pylon::Color);
	bool addBridge(const Position&, const Position&);
	
	bool removeBridge(const Position&, const Position&);
	
	void moveBob();
	void printBoard();

private:
	
	DebuilderBob m_bob;
	bool m_bigPylons;
	bool m_minedFundations;
	bool m_reusableMinedFoundation;
	bool m_debuilderBob;
	bool m_cards;
	Player m_player1;
	Player m_player2;
	Board m_board;
	uint8_t m_areaLength;

	bool validFoundation(const Position&, Pylon::Color);
	bool verifyMinedFoundation(const Position&);
	void explodePylons(const Position&);
	void explodeSingleLocation(const Position&);
	void explodeCol(const Position&);
	void explodeRow(const Position&);
	void explodeArea(const Position&);
};

