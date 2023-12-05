#include "DebuilderBob.h"

using namespace twixt;

DebuilderBob::DebuilderBob(Board& board) : m_board{ board }, m_lastPosition { {} }
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, m_board.get().getSize() - 1);
	m_position = { distrib(gen),  distrib(gen) };
}

twixt::DebuilderBob::DebuilderBob(const DebuilderBob& bob) : m_board{ bob.m_board.get() }
{
	m_position = bob.m_position;
	m_lastPosition = bob.m_lastPosition;
}

DebuilderBob& twixt::DebuilderBob::operator=(const DebuilderBob& bob)
{
	if (this == &bob)
		return *this;

	m_board = bob.m_board;
	m_position = bob.m_position;
	m_lastPosition = bob.m_lastPosition;
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

	m_lastPosition = m_position;
	m_position = position;
	m_board.get().removePylon(position);
	m_board.get()[m_lastPosition.value()].setBob(false);
	m_board.get()[position].setBob(true);
}
