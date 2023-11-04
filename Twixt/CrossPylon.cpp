#include "CrossPylon.h"

CrossPylon::CrossPylon(const Foundation& foundation, Color color):
	Pylon{ foundation, color }
{}

bool CrossPylon::canAddBridge(const Foundation& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation.getPosition());

	if (itFoundation == m_connectionPoints.end() && m_connectionPoints.size() < 2)
		return true;
	else if (itFoundation != m_connectionPoints.end())
		return true;
	return false;
}
