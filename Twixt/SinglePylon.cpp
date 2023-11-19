#include "SinglePylon.h"

SinglePylon::SinglePylon(const Position& foundation, Color color, Type type) :
	Pylon{ foundation, color, type }
{
	m_connectionPoints.emplace_back(foundation);
}

SinglePylon::SinglePylon(const SinglePylon& other) :
	Pylon{ other }
{}

bool SinglePylon::canAddBridge(const Position& foundation) const
{
	return true;
}

bool SinglePylon::addBridge(Bridge* bridge, const Position& foundation)
{
	m_connections.emplace_back(bridge);
	return true;
}

void SinglePylon::removeBridge(Bridge* bridge)
{
	auto it = m_connections.begin();
	while (it != m_connections.end())
	{
		if (*it == bridge)
		{
			m_connections.erase(it);
			return;
		}
		else
			++it;
	}
}



