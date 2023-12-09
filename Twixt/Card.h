#pragma once


class Card
{
	enum class Target
	{
		None,
		Self,
		Opponent
	};

	enum class Effect
	{
		None,
		Draw,
		RemoveCards,
		RemovePylon,
		RemoveBridge,
		Place2Pylons,
		PlaceSquare,
		PlaceCross,
		MoveBob,
		PlaceMine
	};

	Target m_target;
	Effect m_effect;

public:

	Card(Target target = Card::Target::None, Effect effect = Card::Effect::None);
	Card(const Card& other);
	~Card() = default;
	Card& operator=(const Card& other);
	Card(Card&& other) = default;
	Card& operator=(Card&& other) = default;
};

