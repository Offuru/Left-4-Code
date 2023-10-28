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

};

