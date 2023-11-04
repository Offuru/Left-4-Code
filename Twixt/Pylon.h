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

protected:
	std::vector<std::reference_wrapper<const Foundation>> m_foundations;
	std::vector<Bridge*> m_connections; //shared_ptr
	std::vector<std::pair<uint8_t, uint8_t>> m_connectionPoints;
	Color m_color;

public:
	Pylon() = delete;
	Pylon(const Foundation&, Color);
	Pylon(const Pylon&) = delete;
	Pylon& operator=(const Pylon&) = delete;
	virtual ~Pylon() = default;

	std::vector<std::reference_wrapper<const Foundation>> getFoundations() const;
	std::vector<Bridge*> getConnections() const;
	std::vector<std::pair<uint8_t, uint8_t>> getConnectionPoints() const;
	Color getColor() const;

	void setFoundations(const std::vector<std::reference_wrapper<const Foundation>>&);
	void setConnections(const std::vector<Bridge*>&);
	void setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>&);
	void setColor(const Color&);

	void addFoundation(const Foundation&);

	virtual void addBridge(Bridge*) = 0;
};

