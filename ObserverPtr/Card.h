#pragma once
#include <string>
#include <unordered_map>

class Card
{
public:
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
private:
	Effect m_effect;

	//TO DO: move key_val pairs to file and add methods for reading

public:

	__declspec(dllexport) Card(Effect effect = Card::Effect::None);
	__declspec(dllexport) Card(const Card& other);
	__declspec(dllexport) ~Card() = default;
	__declspec(dllexport) Card& operator=(const Card& other);
	__declspec(dllexport) Card(Card&& other) = default;
	__declspec(dllexport) Card& operator=(Card&& other) = default;

	__declspec(dllexport) void setEffect(Effect effect);

	__declspec(dllexport) Effect getEffect() const;
};

