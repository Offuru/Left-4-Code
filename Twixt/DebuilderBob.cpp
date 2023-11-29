#include "DebuilderBob.h"

using namespace twixt;

DebuilderBob::DebuilderBob(uint8_t boardSize) : m_lastPosition{ {} }
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, boardSize - 1);
	m_position = { distrib(gen),  distrib(gen) };
}
Position DebuilderBob::getPosition() const
{
	return m_position;
}

void DebuilderBob::setPosition(const Position& position)
{
	m_position = position;
}

void DebuilderBob::moveToNext(Board& board)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, board.getSize() - 1);
	Position position;

	while (true)
	{
		position = { distrib(gen),  distrib(gen) };
		if (!board[position].getMined() && !(m_lastPosition.has_value() && m_lastPosition.value() == position))
			break;
	}

	m_lastPosition = m_position;
	m_position = position;
	board.removePylon(position);
	board[m_lastPosition.value()].setBob(false);
	board[position].setBob(true);
}
