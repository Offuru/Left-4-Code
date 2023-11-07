#include "Foundation.h"


Foundation::Foundation() :
	m_position{ std::make_pair(0,0) }, m_mined{ false }, m_pylon{ nullptr } {};

Foundation::Foundation(Position position, bool mined, Pylon* pylon) :
	m_position{ position }, m_mined{ mined }, m_pylon{ pylon } {};


Foundation::Foundation(const Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	if (other.getPylon() != nullptr)
	{
		SinglePylon* single = dynamic_cast<SinglePylon*>(other.getPylon());
		if (single)
		{
			m_pylon = new SinglePylon(*single);
			return;
		}
		SquarePylon* square = dynamic_cast<SquarePylon*>(other.getPylon());
		if (square)
		{
			m_pylon = new SquarePylon(*square);
			return;
		}
		CrossPylon* cross = dynamic_cast<CrossPylon*>(other.getPylon());
		if (cross)
		{
			m_pylon = new CrossPylon(*cross);
			return;
		}
	}
	m_pylon = nullptr;
}

Foundation& Foundation::operator=(Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	
	if (m_pylon)
		delete m_pylon;

	SinglePylon* single = dynamic_cast<SinglePylon*>(other.getPylon());
	if (single)
	{
		m_pylon = new SinglePylon(*single);
		return *this;
	}
	SquarePylon* square = dynamic_cast<SquarePylon*>(other.getPylon());
	if (square)
	{
		m_pylon = new SquarePylon(*square);
		return *this;
	}
	CrossPylon* cross = dynamic_cast<CrossPylon*>(other.getPylon());
	if (cross)
	{
		m_pylon = new CrossPylon(*cross);
		return *this;
	}

	m_pylon = nullptr;
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
