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

	static std::unordered_map<Target, std::string> targets;
	static std::unordered_map<Effect, std::string> effects;
	//TO DO: move key_val pairs to file and add methods for reading

public:

	Card(Target target = Card::Target::None, Effect effect = Card::Effect::None);
	Card(const Card& other);
	~Card() = default;
	Card& operator=(const Card& other);
	Card(Card&& other) = default;
	Card& operator=(Card&& other) = default;

	void setTarget(Target target);
	void setEffect(Effect effect);

	Target getTarget() const;
	Effect getEffect() const;

	std::string getTargetString() const;
	std::string getEffectString() const;
};

