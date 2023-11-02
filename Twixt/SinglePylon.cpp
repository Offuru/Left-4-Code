#include "SinglePylon.h"

SinglePylon::SinglePylon(const Foundation& foundation, Color color):
	Pylon{ foundation,color }
{
	m_connectionPoints.emplace_back(foundation.getPosition());
}


void SinglePylon::addBridge(Bridge* bridge)
{
	m_connections.emplace_back(bridge);
}



