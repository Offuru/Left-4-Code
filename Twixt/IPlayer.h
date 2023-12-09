#pragma once
#include <string>
#include <tuple>
#include <optional>
#include <string_view>
#include "Utilities.h"
#include "Pylon.h"
#include "Card.h"
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
			PlayCard,

		};

		// optional position in case of add/remove bridge action
		using Move = std::tuple<Action, std::optional<Position>, std::optional<Position>>;

		IPlayer(const std::string& name = "");

		IPlayer(const IPlayer&) = default;
		IPlayer(IPlayer&&) = default;
		IPlayer& operator=(const IPlayer&) = default;
		IPlayer& operator=(IPlayer&&) = default;
		virtual ~IPlayer() = default;

		void draw(std::stack<Card>&);
		virtual Move getNextMove() = 0;
		bool validMove(const Move&, uint8_t) const;//TO DO: define to check 
										  //whether or not move was valid (position, color, noPieces, etc)

		void setName(const std::string&);
		void setColor(Pylon::Color);
		void setNoBridges(uint8_t);
		void setNoPylons1x1(uint8_t);
		void setNoPylons2x2(uint8_t);
		void setNoPylonsCross(uint8_t);
		void setCards(const std::vector<Card>&);

		std::string getName() const;
		Pylon::Color getColor() const;
		uint8_t getNoBridges() const;
		uint8_t getNoPylons1x1() const;
		uint8_t getNoPylons2x2() const;
		uint8_t getNoPylonsCross() const;
		std::vector<Card> getCards() const;

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