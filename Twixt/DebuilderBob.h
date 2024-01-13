#pragma once
#include <utility>
#include <random>
#include <optional>
#include "Board.h"
#include "Utilities.h"

namespace twixt
{

	class Board;

	class DebuilderBob
	{
	private:
		Position m_position;
		std::optional<Position> m_lastPosition;
		std::reference_wrapper<Board> m_board;

	public:
		DebuilderBob(Board&);
		DebuilderBob(const DebuilderBob&);
		~DebuilderBob() = default;
		DebuilderBob& operator=(const DebuilderBob&);

		Position getPosition() const;
		void setPosition(const Position&);

		void moveToNext(const std::optional<Position>&);
	};
}