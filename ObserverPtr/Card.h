#pragma once
#include <string>
#include <unordered_map>

class Card
{
public:
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

private:
	Target m_target;
	Effect m_effect;

	//TO DO: move key_val pairs to file and add methods for reading

public:
	static std::unordered_map<Target, std::string> targets;
	static std::unordered_map<Effect, std::string> effects;

	__declspec(dllexport) Card(Target target = Card::Target::None, Effect effect = Card::Effect::None);
	__declspec(dllexport) Card(Effect effect);
	__declspec(dllexport) Card(const Card& other);
	__declspec(dllexport) ~Card() = default;
	__declspec(dllexport) Card& operator=(const Card& other);
	__declspec(dllexport) Card(Card&& other) = default;
	__declspec(dllexport) Card& operator=(Card&& other) = default;

	__declspec(dllexport) void setTarget(Target target);
	__declspec(dllexport) void setEffect(Effect effect);

	__declspec(dllexport) Target getTarget() const;
	__declspec(dllexport) Effect getEffect() const;

	__declspec(dllexport) std::string getTargetString() const;
	__declspec(dllexport) std::string getEffectString() const;
};

