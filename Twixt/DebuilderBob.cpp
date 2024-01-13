#include "DebuilderBob.h"

using namespace twixt;

DebuilderBob::DebuilderBob(Board& board) : m_board{ board }, m_lastPosition{ {} }, m_position{} {}

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

void DebuilderBob::moveToNext(const std::optional<Position>& nextPos)
{
	Position position;

	if (!nextPos.has_value())
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(0, m_board.get().getSize() - 1);

		std::bernoulli_distribution d(0.1);

		bool killerBob = d(gen);

		if (killerBob)
		{
			uint8_t size = 0;
			for (const auto& it : m_board.get().getPylons())
			{
				++size;
			}
			std::uniform_int_distribution<> randomPylon(0, size);
			int index = randomPylon(gen);

			for (auto itr = m_board.get().getPylons().begin(); itr != m_board.get().getPylons().end(); ++itr, --index)
			{
				if (index == 0)
				{
					m_board.get().removePylon(itr->first);
					break;
				}

			}
		}

		else
		{
			std::array<Position, 4> corners { std::make_pair(0, 0), {0, m_board.get().getSize() - 1},
				{m_board.get().getSize() - 1, 0}, {m_board.get().getSize() - 1, m_board.get().getSize() - 1} };

			while (true)
			{
				position = { distrib(gen),  distrib(gen) };
				if (!m_board.get()[position].getMined() && !(m_lastPosition.has_value() && m_lastPosition.value() == position) 
					&& m_board.get()[position].getPylon() == nullptr
					&& std::ranges::find(corners, position) == corners.end())
					break;
			}
		}
	}
	else {
		position = nextPos.value();
	}

	m_lastPosition = m_position;
	m_position = position;
	m_board.get().removePylon(position);
	m_board.get()[m_lastPosition.value()].setBob(false);
	m_board.get()[position].setBob(true);
}
