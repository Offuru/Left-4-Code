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

void Game::setBigPylons(bool bigPylons)
{
	m_bigPylons = bigPylons;
}

void Game::setMinedFoundations(bool minedFoundations)
{
	m_minedFundations = minedFoundations;
}

void Game::setDebuilderBob(bool debuilderBob)
{
	m_debuilderBob = debuilderBob;
}

void Game::setCards(bool cards)
{
	m_cards = cards;
}

void Game::setPlayer1(const Player& player)
{
	m_player1 = player;
}

void Game::setPlayer2(const Player& player)
{
	m_player2 = player;
}

void Game::setBoard(const Board& board) 
{
	m_board = board;
}

bool Game::getBigPylons() const
{
	return m_bigPylons;
}

bool Game::getMinedFoundations() const
{
	return m_minedFundations;
}

bool Game::getDebuilderBob() const
{
	return m_debuilderBob;
}

Player Game::getPlayer1() const
{
	return m_player1;
}

Player Game::getPlayer2() const
{
	return m_player2;
}

Board Game::getBoard() const
{
	return m_board;
}

bool Game::getCards() const
{
	return m_cards;
}
