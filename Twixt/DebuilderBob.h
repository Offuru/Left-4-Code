#pragma once
#include <utility>;
#include <random>;
#include <optional>
#include "Board.h";
using Position = std::pair<uint8_t, uint8_t>;

class DebuilderBob
{
private:
	Position m_position;
	std::optional<Position> m_lastPosition;
	std::reference_wrapper<Board> m_board;

public:
	DebuilderBob(Board&);
	DebuilderBob(const DebuilderBob&) = default;
	~DebuilderBob() = default;
	DebuilderBob& operator=(const DebuilderBob&) = default;

	Position getPosition() const;
	void setPosition(const Position&);

	void moveToNext();
};
