#include "Player.h"

using namespace twixt;

Player::Player() :
	m_color{ Pylon::Color::Red }, m_noBridges{ 50 }, m_noPylons1x1{ 50 }, m_noPylons2x2{ 5 }, m_noPylonsCross{ 5 } {}

Player::Player(const Player& other) :
	m_color{ other.m_color }, m_noBridges{ other.m_noBridges }, m_noPylons1x1{ other.m_noPylons1x1 },
	m_noPylons2x2{ other.m_noPylons2x2 }, m_noPylonsCross{ other.m_noPylonsCross } {}

Player& Player::operator=(const Player& other)
{
	m_color = other.m_color;
	m_noBridges = other.m_noBridges;
	m_noPylons1x1 = other.m_noPylons1x1;
	m_noPylons2x2 = other.m_noPylons2x2;
	m_noPylonsCross = other.m_noPylonsCross;

	return *this;
}

void Player::setColor(Pylon::Color color)
{
	m_color = color;
}

void Player::setNoBridges(uint8_t noBridges)
{
	m_noBridges = noBridges;
}

void Player::setNoPylons1x1(uint8_t noPylons1x1)
{
	m_noPylons1x1 = noPylons1x1;
}

void Player::setNoPylons2x2(uint8_t noPylons2x2)
{
	m_noPylons2x2 = noPylons2x2;
}

void Player::setNoPylonsCross(uint8_t noPylonsCross)
{
	m_noPylonsCross = noPylonsCross;
}

Pylon::Color Player::getColor() const
{
	return m_color;
}

uint8_t Player::getNoBridges() const
{
	return m_noBridges;
}

uint8_t Player::getNoPylons1x1() const
{
	return m_noPylons1x1;
}

uint8_t Player::getNoPylons2x2() const
{
	return m_noPylons2x2;
}

uint8_t Player::getNoPylonsCross() const
{
	return m_noPylonsCross;
}
