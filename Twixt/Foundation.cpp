#include "Foundation.h"

Foundation::Foundation() :
	m_position{ std::make_pair(0,0) }, m_mined{ false }, m_pylon{ nullptr } {};

Foundation::Foundation(Position position, bool mined, Pylon* pylon) :
	m_position{ position }, m_mined{ mined }, m_pylon{ pylon } {};

Foundation::Foundation(const Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	m_pylon = other.m_pylon;//Multiple foundations ca point to the same pylon (2x2 & cross pylons)
}

Foundation& Foundation::operator=(const Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	m_pylon = other.m_pylon;

	return *this;
}

Foundation::~Foundation()
{
	if(m_pylon)
		delete m_pylon;
}

Position Foundation::getPosition() const
{
	return m_position;
}

bool Foundation::getMined() const
{
	return m_mined;
}

Pylon* Foundation::getPylon() const
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

void Foundation::setPylon(Pylon* pylon)
{
	m_pylon = pylon;
}
