#pragma once
#include <utility>;
#include <random>;
#include "Board.h";
using Position = std::pair<uint8_t, uint8_t>;

class DebuilderBob
{
private:
	Position m_position;

public:
	DebuilderBob(uint8_t = 24);
	DebuilderBob(const DebuilderBob&) = default;
	~DebuilderBob() = default;
	DebuilderBob& operator=(const DebuilderBob&) = default;

	Position getPosition() const;
	void setPosition(const Position&);

};
