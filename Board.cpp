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
