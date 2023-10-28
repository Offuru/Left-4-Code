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

private:
	bool m_bigPylons;
	bool m_minedFundations;
	bool m_debuilderBob;
	bool m_cards;
	Player m_player1;
	Player m_player2;
	Board m_board;
};

