#include "Player.h"

Player::Player()
{
	m_color = Pylon::Color::Red;
	m_noBridges = 50;
	m_noPylons1x1 = 50;
	m_noPylons2x2 = 5;
	m_noPylonsCross = 5;
}

Player::Player(const Player& other)
{
	m_color = other.m_color;
	m_noBridges = other.m_noBridges;
	m_noPylons1x1 = other.m_noPylons1x1;
	m_noPylons2x2 = other.m_noPylons2x2;
	m_noPylonsCross = other.m_noPylonsCross;
}

Player& Player::operator=(const Player& other)
{
	m_color = other.m_color;
	m_noBridges = other.m_noBridges;
	m_noPylons1x1 = other.m_noPylons1x1;
	m_noPylons2x2 = other.m_noPylons2x2;
	m_noPylonsCross = other.m_noPylonsCross;

	return *this;
}
