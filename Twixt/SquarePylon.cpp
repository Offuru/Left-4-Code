#include "SquarePylon.h"

SquarePylon::SquarePylon(const Position& foundation, Color color, Type type): 
	Pylon{foundation, color, type}
{}

SquarePylon::SquarePylon(const SquarePylon& other):
	Pylon{ other }
{}

bool SquarePylon::canAddBridge(const Position& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);

	if (itFoundation == m_connectionPoints.end() && m_connectionPoints.size() < 2)
		return true;
	else if (itFoundation != m_connectionPoints.end()) 
		return true;
	return false;
}

bool SquarePylon::addBridge(Bridge* bridge, const Position& foundation)
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);
	if (itFoundation == m_connectionPoints.end() &&  m_connectionPoints.size() < 2)
	{
		m_connections.emplace_back(bridge);
		m_connectionPoints.emplace_back(foundation);
		return true;
	}
	else if (itFoundation != m_connectionPoints.end()){
		m_connections.emplace_back(bridge);
		return true;
	}
	return false;
}
