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

	public:
		DebuilderBob(uint8_t = 24); //TO DO: get rid of magic number
		DebuilderBob(const DebuilderBob&) = default;
		~DebuilderBob() = default;
		DebuilderBob& operator=(const DebuilderBob&) = default;

		Position getPosition() const;
		void setPosition(const Position&);

		void moveToNext(Board&);
	};
}