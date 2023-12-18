#include "Foundation.h"

using namespace twixt;

Foundation::Foundation() :
	m_position{ std::make_pair(0,0) }, m_mined{ false }, m_exploded{ false }, m_pylon{ nullptr }, m_hasBob{ false } {}

Foundation::Foundation(Position position, bool mined, nonstd::observer_ptr<Pylon> pylon) :
	m_position{ position }, m_mined{ mined }, m_exploded{ false }, m_pylon{ pylon }, m_hasBob{ false } {};


Foundation::Foundation(const Foundation& other) :
	m_exploded{ other.m_exploded }, m_position{ other.m_position }, 
	m_hasBob{ other.m_hasBob }, m_mined{ other.m_mined }
{} 

Foundation& Foundation::operator=(Foundation& other)
{
	m_exploded = other.m_exploded;
	m_position = other.m_position;
	m_mined = other.m_mined;
	m_hasBob = other.m_hasBob;

	return *this;
}

Position Foundation::getPosition() const
{
	return m_position;
}

bool Foundation::getMined() const
{
	return m_mined;
}

bool Foundation::getExploded() const
{
	return m_exploded;
}

bool Foundation::getBob() const
{
	return m_hasBob;
}

nonstd::observer_ptr<Pylon> Foundation::getPylon() const
{
	return m_pylon;
}

void Foundation::setPosition(const Position& position)
{
	m_position = position;
}

void Foundation::setMined(bool mined)
{
	m_mined = mined;
}

void Foundation::setExploded(bool exploded)
{
	m_exploded = exploded;
}

void Foundation::setPylon(nonstd::observer_ptr<Pylon> pylon)
{
	m_pylon = pylon;
}

void Foundation::setBob(bool hasBob)
{
	m_hasBob = hasBob;
}
