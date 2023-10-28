#include "Game.h"

Game::Game()
{
	m_bigPylons = m_minedFundations 
		= m_debuilderBob = m_cards = false;
	m_player1 = Player();
	m_player2 = Player();
	m_player2.setColor(Pylon::Color::Black);
	m_board = Board();
}

Game::Game(const Game& other)
{
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;
}

Game& Game::operator=(const Game& other)
{
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;

	return *this;
}
