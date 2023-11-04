#include "SinglePylon.h"

SinglePylon::SinglePylon(const Foundation& foundation, Color color):
	Pylon{ foundation,color }
{
	m_connectionPoints.emplace_back(foundation.getPosition());
}

bool SinglePylon::canAddBridge(const Foundation& foundation) const
{
	return true;
}

bool SinglePylon::addBridge(Bridge* bridge, const Foundation& foundation)
{
	m_connections.emplace_back(bridge);
	return true;
}



