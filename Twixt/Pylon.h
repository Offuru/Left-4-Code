#pragma once

#include <vector>
#include <functional>
#include <unordered_set>
#include "Bridge.h"
#include "Utilities.h"
//#include "Foundation.h"

namespace twixt
{
	class Bridge;

	class Pylon
	{
	public:
		enum class Color
		{
			Red,
			Black
		};

		enum class Type
		{
			Single,
			Square,
			Cross
		};

	protected:
		std::vector<Position> m_foundations;
		std::vector<std::shared_ptr<Bridge>> m_connections;
		std::vector<Position> m_connectionPoints;
		Color m_color;
		Type m_type;

	public:
		Pylon() = delete;
		Pylon(const Position&, Color, Type);
		Pylon(const Pylon&);
		Pylon& operator=(const Pylon&);
		virtual ~Pylon() = default;

		std::vector<Position> getFoundations() const; //first foundation is always the one that "spawns" the pylon (center for cross and single, top left corner for square)
		std::vector<std::shared_ptr<Bridge>> getConnections() const;
		std::vector<Position> getConnectionPoints() const; //TO DO: change to predefined pylon connection points
		Color getColor() const;
		Type getType() const;

		void setFoundations(const std::vector<Position>&);
		void setConnections(const std::vector<std::shared_ptr<Bridge>>&);
		void setConnectionPoints(const std::vector<Position>&); //TO DO: change to predefined pylon connection points
		void setColor(const Color&);

		void addFoundation(const Position&);

		virtual bool canAddBridge(const Position&) const = 0;
		virtual bool addBridge(std::shared_ptr<Bridge>, const Position&) = 0;
		virtual void removeBridge(std::shared_ptr<Bridge>) = 0;
	};
}

namespace std
{
	template<>
	struct hash<twixt::Position>
	{
		const size_t operator () (twixt::Position const& p) const
		{
			return (std::hash<uint8_t>()(p.first) + std::hash<uint8_t>()(p.second));
		}
	};
}