#pragma once

#include <vector>
#include <functional>
#include "Bridge.h"
#include "Foundation.h"

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

private:
	std::reference_wrapper<const Foundation> m_position;
	std::vector<std::reference_wrapper<const Bridge>> m_connections;
	std::vector<std::pair<uint8_t, uint8_t>> m_connectionPoints;
	Color m_color;

public:
	Pylon() = delete;
	Pylon(const Foundation&, Color);
	Pylon(const Pylon&);
	Pylon& operator=(const Pylon&);
	virtual ~Pylon() = default;

	const Foundation& getPosition() const;
	std::vector<std::reference_wrapper<const Bridge>> getConnections() const;
	std::vector<std::pair<uint8_t, uint8_t>> getConnectionPoints() const;
	Color getColor() const;

	void setFoundation(const Foundation&);
	void setConnections(const std::vector<std::reference_wrapper<const Bridge>>&);
	void setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>&);
	void setColor(const Color&);
};

