#include "Board.h"

Board::Board()
{
	m_board.resize(m_size);
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			m_board[i].emplace_back(Foundation(std::make_pair(i, j)));
		}
	}
}

Board::Board(const Board& other)
{
	m_board = other.m_board;
	m_pylons = other.m_pylons;
	m_bridges = other.m_bridges;
}

Board& Board::operator=(const Board& other)
{
	m_board = other.m_board;
	m_pylons = other.m_pylons;
	m_bridges = other.m_bridges;

	return *this;
}

Board::~Board()
{
	for (auto& line : m_board)
		for (auto& foundation : line)
			delete foundation.getPylon();
}

std::vector<std::vector<Foundation>> Board::getBoard() const
{
	return m_board;
}

std::map<std::pair<uint8_t, uint8_t>, Pylon*> Board::getPylons() const
{
	return m_pylons;
}

std::multimap<Pylon*, Bridge*> Board::getBridges() const
{
	return m_bridges;
}

void Board::setBoard(const std::vector<std::vector<Foundation>>& other)
{
	m_board = other;
}

void Board::setPylons(const std::map<std::pair<uint8_t, uint8_t>, Pylon*>& other)
{
	m_pylons = other;
}

void Board::setBridges(const std::multimap<Pylon*, Bridge*>& other)
{
	m_bridges = other;
}


