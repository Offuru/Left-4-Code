#pragma once
#include <string>
#include <tuple>
#include <optional>
#include <string_view>
//#include "Utilities.h"
#include "../ObserverPtr/Pylon.h"
#include "../ObserverPtr/Card.h"
#include <stack>

namespace twixt
{
	class IPlayer
	{
	public:

		enum class Action : uint8_t {

			AddSinglePylon,
			AddSquarePylon,
			AddCrossPylon,
			AddBridge,
			RemovePylon,
			RemoveBridge,
			DrawCard,
			PlayCard
		};

		// optional position in case of add/remove bridge action
		using Move = std::tuple<Action, std::optional<Position>, std::optional<Position>>;

		__declspec(dllexport) IPlayer(const std::string& name = "");

		__declspec(dllexport) IPlayer(const IPlayer&) = default;
		__declspec(dllexport) IPlayer(IPlayer&&) = default;
		__declspec(dllexport) IPlayer& operator=(const IPlayer&) = default;
		__declspec(dllexport) IPlayer& operator=(IPlayer&&) = default;
		__declspec(dllexport) virtual ~IPlayer() = default;

		__declspec(dllexport) void removeCard(size_t index);
		__declspec(dllexport) void draw(std::stack<Card>&);
		__declspec(dllexport) virtual Move getNextMove() = 0;
		__declspec(dllexport) bool validMove(const Move&, uint8_t) const;//TO DO: define to check 
		 //whether or not move was valid (position, color, noPieces, etc)

		__declspec(dllexport) void setName(const std::string&);
		__declspec(dllexport) void setColor(Pylon::Color);
		__declspec(dllexport) void setNoBridges(uint8_t);
		__declspec(dllexport) void setNoPylons1x1(uint8_t);
		__declspec(dllexport) void setNoPylons2x2(uint8_t);
		__declspec(dllexport) void setNoPylonsCross(uint8_t);
		__declspec(dllexport) void setCards(const std::vector<Card>&);
		
		__declspec(dllexport) std::string getName() const;
		__declspec(dllexport) Pylon::Color getColor() const;
		__declspec(dllexport) uint8_t getNoBridges() const;
		__declspec(dllexport) uint8_t getNoPylons1x1() const;
		__declspec(dllexport) uint8_t getNoPylons2x2() const;
		__declspec(dllexport) uint8_t getNoPylonsCross() const;
		__declspec(dllexport) std::vector<Card> getCards() const;
		__declspec(dllexport) virtual std::string getTypeString() = 0;

	protected:

		std::vector<Card> m_cards;
		std::string m_name;
		Pylon::Color m_color : 2;
		uint8_t m_noBridges;
		uint8_t m_noPylons1x1;
		uint8_t m_noPylons2x2;
		uint8_t m_noPylonsCross;

	};
}