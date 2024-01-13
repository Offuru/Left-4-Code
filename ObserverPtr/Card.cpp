#include "Card.h"

using namespace twixt;

twixt::Card::Card()
{
	m_effect = Effect::Draw;
}

Card::Card(Effect effect)
{
	m_effect = effect;
}

Card::Card(const Card& other)
{
	m_effect = other.m_effect;
}

Card& Card::operator=(const Card& other)
{
	m_effect = other.m_effect;
	return *this;
}

void Card::setEffect(Effect effect)
{
	m_effect = effect;
}

Card::Effect Card::getEffect() const
{
	return m_effect;
}
