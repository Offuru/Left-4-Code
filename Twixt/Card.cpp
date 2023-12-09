#include "Card.h"

Card::Card(Target target, Effect effect)
{
	m_target = target;
	m_effect = effect;
}

Card::Card(const Card& other)
{
	m_target = other.m_target;
	m_effect = other.m_effect;
}

Card& Card::operator=(const Card& other)
{
	m_target = other.m_target;
	m_effect = other.m_effect;
	return *this;
}
