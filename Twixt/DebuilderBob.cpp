#include "DebuilderBob.h"

DebuilderBob::DebuilderBob(Board& board) : m_board{ board }, m_lastPosition{ {} }
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, m_board.get().getSize() - 1);
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

void DebuilderBob::moveToNext()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, m_board.get().getSize() - 1);
	Position position;

	while (true)
	{
		position = { distrib(gen),  distrib(gen) };
		
		if (!m_board.get()[position].getMined() && !(m_lastPosition.has_value() && m_lastPosition.value() == position))
			break;
	}

	//TO DO: destroy pylon from board if on foundation
	m_lastPosition = m_position;
	m_position = position;
}
