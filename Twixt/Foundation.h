#pragma once

#include <utility>
#include "Pylon.h"
#include "CrossPylon.h"
#include "SinglePylon.h"
#include "SquarePylon.h"

using Position = std::pair<uint8_t, uint8_t>;

class Pylon;

class Foundation
{
private:
	Position m_position;
	bool m_mined;
	Pylon* m_pylon;

public:
	Foundation();
	Foundation(Position, bool = false, Pylon* = nullptr);
	Foundation(const Foundation&);
	Foundation& operator=(Foundation&);
	~Foundation() = default; // pilonii se distrug din board!!

	Position getPosition() const;
	bool getMined() const;
	Pylon* getPylon() const;

	void setPosition(const Position&);
	void setMined(bool);
	void setPylon(Pylon*);
};

