#include "CrossPylon.h"

using namespace twixt;

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

bool CrossPylon::addBridge(std::shared_ptr<Bridge> bridge, const Position& foundation)
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

void CrossPylon::removeBridge(std::shared_ptr<Bridge> bridge)
{
	auto it = m_connections.begin();
	while (it != m_connections.end())
	{
		if (*it == bridge)
		{
			m_connections.erase(it);
			break;
		}
		else
			++it;
	}

	std::unordered_set<Position> usedPositions;
	for (auto bridge : m_connections)
	{
		usedPositions.insert(bridge->getPosStart());
		usedPositions.insert(bridge->getPosEnd());
	}

	for (auto connectionPoint = m_connectionPoints.begin(); connectionPoint != m_connectionPoints.end();)
	{
		if (usedPositions.find(*connectionPoint) == usedPositions.end())
		{
			connectionPoint = m_connectionPoints.erase(connectionPoint);
		}
		else
		{
			++connectionPoint;
		}
	}
}
