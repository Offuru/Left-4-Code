#pragma once

#include <vector>
#include <functional>
#include "Bridge.h"
#include "Foundation.h"

using Position = std::pair<uint8_t, uint8_t>;

class Bridge;
class Foundation;

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
	std::vector<std::reference_wrapper<const Foundation>> m_foundations;
	std::vector<Bridge*> m_connections; //shared_ptr
	std::vector<Position> m_connectionPoints;
	Color m_color;

public:
	Pylon() = delete;
	Pylon(const Foundation&, Color);
	Pylon(const Pylon&) = delete;
	Pylon& operator=(const Pylon&) = delete;
	virtual ~Pylon() = default;

	std::vector<std::reference_wrapper<const Foundation>> getFoundations() const;
	std::vector<Bridge*> getConnections() const;
	std::vector<Position> getConnectionPoints() const;
	Color getColor() const;

	void setFoundations(const std::vector<std::reference_wrapper<const Foundation>>&);
	void setConnections(const std::vector<Bridge*>&);
	void setConnectionPoints(const std::vector<Position>&);
	void setColor(const Color&);

	void addFoundation(const Foundation&);

	virtual bool canAddBridge(const Foundation&) const = 0;
	virtual bool addBridge(Bridge*, const Foundation&) = 0;
};

