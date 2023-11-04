#include "SquarePylon.h"

SquarePylon::SquarePylon(const Foundation& foundation, Color color) : Pylon{foundation, color}
{}

bool SquarePylon::canAddBridge(const Foundation& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation.getPosition());

	if (itFoundation == m_connectionPoints.end() && m_connectionPoints.size() < 2)
		return true;
	else if (itFoundation != m_connectionPoints.end()) 
		return true;
	return false;
}

bool SquarePylon::addBridge(Bridge* bridge, const Foundation& foundation)
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation.getPosition());
	if (itFoundation == m_connectionPoints.end() &&  m_connectionPoints.size() < 2)
	{
		m_connections.emplace_back(bridge);
		m_connectionPoints.emplace_back(foundation.getPosition());
		return true;
	}
	else if (itFoundation != m_connectionPoints.end()){
		m_connections.emplace_back(bridge);
		return true;
	}
	return false;
}
