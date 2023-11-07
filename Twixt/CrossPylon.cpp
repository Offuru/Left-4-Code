#include "CrossPylon.h"

CrossPylon::CrossPylon(const Position& foundation, Color color, Type type):
	Pylon{ foundation, color, type }
{}

CrossPylon::CrossPylon(const CrossPylon& other) :
	Pylon{ other }
{}

bool CrossPylon::canAddBridge(const Position& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);

	if (itFoundation == m_connectionPoints.end() && m_connectionPoints.size() < 2)
		return true;
	else if (itFoundation != m_connectionPoints.end())
		return true;
	return false;
}

bool CrossPylon::addBridge(Bridge* bridge, const Position& foundation)
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);
	if (itFoundation == m_connectionPoints.end() && m_connectionPoints.size() < 2)
	{
		m_connections.emplace_back(bridge);
		m_connectionPoints.emplace_back(foundation);
		return true;
	} else if (itFoundation != m_connectionPoints.end())
	{
		m_connections.emplace_back(bridge);
		return true;
	}
	return false;
}
