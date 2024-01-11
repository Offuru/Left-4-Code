#include "Card.h"

std::unordered_map<Card::Target, std::string> Card::targets{
		{Target::None, "None"}, {Target::Self, "Self"}, {Target::Opponent, "Opponent"} };
std::unordered_map<Card::Effect, std::string> Card::effects{
	{Effect::None, "None"}, { Effect::Draw, "Draw" }, { Effect::RemoveCards, "RemoveCards" },
	{ Effect::RemovePylon, "RemovePylon" }, { Effect::RemoveBridge, "RemoveBridge" },
	{ Effect::Place2Pylons, "Place2Pylons" }, { Effect::PlaceSquare, "PlaceSquare" }, { Effect::PlaceCross,"PlaceCross" },
	{ Effect::MoveBob, "MoveBob" }, { Effect::PlaceMine, "PlaceMine" } }; //TO DO: move to txt file

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

void Card::setTarget(Target target)
{
	m_target = target;
}

void Card::setEffect(Effect effect)
{
	m_effect = effect;
}

Card::Target Card::getTarget() const
{
	return m_target;
}

Card::Effect Card::getEffect() const
{
	return m_effect;
}

std::string Card::getTargetString() const
{
	return targets[m_target];
}

std::string Card::getEffectString() const
{
	return effects[m_effect];
}
