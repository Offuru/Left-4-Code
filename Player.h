#pragma once
#include "Pylon.h"

class Player
{
private:

	Pylon::Color m_color;
	uint8_t m_noBridges;
	uint8_t m_noPylons1x1;
	uint8_t m_noPylons2x2;
	uint8_t m_noPylonsCross;

public:
	
	Player();
	Player(const Player&);
	~Player() = default;
	Player& operator=(const Player&);

	void setColor(Pylon::Color);
	void setNoBridges(uint8_t);
	void setNoPylons1x1(uint8_t);
	void setNoPylons2x2(uint8_t);
	void setNoPylonsCross(uint8_t);
	
	Pylon::Color getColor() const;
	uint8_t getNoBridges() const;
	uint8_t getNoPylons1x1() const;
	uint8_t getNoPylons2x2() const;
	uint8_t getNoPylonsCross() const;
};

