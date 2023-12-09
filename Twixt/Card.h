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

	Target target;
	Effect effect;
};

