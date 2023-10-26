#pragma once

#include <vector>
#include "Bridge.h"
#include "Foundation.h"

class Pylon
{
public:
	static enum class Color
	{
		Red,
		Black
	};

private:
	Foundation* m_position;
	std::vector<Bridge*> m_connections;
	std::vector<std::pair<uint8_t, uint8_t>> m_connectionPoints;
	Color m_color;

public:
	Pylon();
	Pylon(Foundation*, Color);
	Pylon(const Pylon&);
	Pylon& operator=(const Pylon&);
	virtual ~Pylon();

	Foundation* getPosition() const;
	std::vector<Bridge*> getConnections() const;
	std::vector<std::pair<uint8_t, uint8_t>> getConnectionPoints() const;
	Color getColor() const;

	void setFoundation(Foundation*);
	void setConnections(const std::vector<Bridge*>&);
	void setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>&);
	void setColor(const Color&);
};

