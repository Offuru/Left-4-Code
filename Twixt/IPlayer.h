#pragma once
#include <string>
#include <tuple>
#include <optional>
#include <string_view>
#include "Pylon.h"

class IPlayer
{
public:

	enum class Action : uint8_t {

		AddSinglePylon,
		AddSquarePylon,
		AddCrossPylon,
		AddBridge,
		RemovePylon,
		RemoveBridge

	};

	using Position = std::pair<uint8_t, uint8_t>;
	using Move = std::tuple<Action, Position, std::optional<Position>>;
	
	IPlayer(const std::string& name = "");

	IPlayer(const IPlayer&) = default;
	IPlayer(IPlayer&&) = default;
	IPlayer& operator=(const IPlayer&) = default;
	IPlayer& operator=(IPlayer&&) = default;
	virtual ~IPlayer() = default;


	virtual Move getNextMove() = 0;

	void setColor(Pylon::Color);
	void setNoBridges(uint8_t);
	void setNoPylons1x1(uint8_t);
	void setNoPylons2x2(uint8_t);
	void setNoPylonsCross(uint8_t);

	Pylon::Color getColor() const;
	uint8_t getNoBridges() const;
	uint8_t getNoPylons1x1() const;
	uint8_t getNoPylons2x2() const;
	uint8_t getNoPylonsCross() const;

protected:

	std::string name;
	Pylon::Color m_color : 1;
	uint8_t m_noBridges;
	uint8_t m_noPylons1x1;
	uint8_t m_noPylons2x2;
	uint8_t m_noPylonsCross;

};

