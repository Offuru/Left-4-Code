#pragma once

#include <vector>
#include <functional>
#include <unordered_set>
#include "Bridge.h"
#include "observer_ptr.h"

namespace twixt
{
	using Position = std::pair<uint8_t, uint8_t>;

	template<class Derived, class Base>
	bool instanceOf(Derived* derived)
	{
		return dynamic_cast<Base*>(derived) != nullptr;
	}

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
		using Position = std::pair<uint8_t, uint8_t>;
		std::vector<Position> m_foundations;
		std::vector<nonstd::observer_ptr<Bridge>> m_connections;
		std::vector<Position> m_connectionPoints;
		Color m_color;
		Type m_type;
		uint8_t m_pylonRotation;
		bool m_bigConfiguration;

	public:
		__declspec(dllexport) Pylon() = delete;
		__declspec(dllexport) Pylon(const Position&, Color, Type, uint8_t pylonRotation, bool bigConfiguration);
		__declspec(dllexport) Pylon(const Pylon&);
		__declspec(dllexport) Pylon& operator=(const Pylon&);
		__declspec(dllexport) virtual ~Pylon() = default;

		__declspec(dllexport) std::vector<Position> getFoundations() const; //first foundation is always the one that "spawns" the pylon (center for cross and single, top left corner for square)
		__declspec(dllexport) std::vector<nonstd::observer_ptr<Bridge>> getConnections() const;
		__declspec(dllexport) std::vector<Position> getConnectionPoints() const; //TO DO: change to predefined pylon connection points
		__declspec(dllexport) Color getColor() const;
		__declspec(dllexport) Type getType() const;
		__declspec(dllexport) bool getPylonRotation() const;
		__declspec(dllexport) uint8_t getBigConfiguration() const;

		__declspec(dllexport) void setFoundations(const std::vector<Position>&);
		__declspec(dllexport) void setConnections(const std::vector<nonstd::observer_ptr<Bridge>>&);
		__declspec(dllexport) void setConnectionPoints(const std::vector<Position>&); //TO DO: change to predefined pylon connection points
		__declspec(dllexport) void setColor(const Color&);

		__declspec(dllexport) void addFoundation(const Position&);

		__declspec(dllexport) virtual bool canAddBridge(const Position&) const = 0;
		__declspec(dllexport) virtual bool addBridge(nonstd::observer_ptr<Bridge>, const Position&) = 0;
		__declspec(dllexport) virtual void removeBridge(nonstd::observer_ptr<Bridge>) = 0;
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