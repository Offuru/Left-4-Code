#pragma once
#include "Player.h"
#include "Board.h"

class Game
{
public:

	Game();
	Game(const Game&);
	Game& operator=(const Game&);
	~Game() = default;

	void setBigPylons(bool);
	void setMinedFoundations(bool);
	void setDebuilderBob(bool);
	void setCards(bool);
	void setPlayer1(const Player&);
	void setPlayer2(const Player&);
	void setBoard(const Board&);

	bool getBigPylons() const;
	bool getMinedFoundations() const;
	bool getDebuilderBob() const;
	bool getCards() const;
	Player getPlayer1() const;
	Player getPlayer2() const;
	Board getBoard() const;

private:
	bool m_bigPylons;
	bool m_minedFundations;
	bool m_debuilderBob;
	bool m_cards;
	Player m_player1;
	Player m_player2;
	Board m_board;

};

