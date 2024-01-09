#include "CrossPylon.h"

using namespace twixt;

CrossPylon::CrossPylon(const Position& foundation, Color color, Type type, uint8_t pylonRotation, bool bigConfiguration) :
	Pylon{ foundation, color, type, pylonRotation, bigConfiguration }
{
	int dx[4] = { 0, 1, 0, -1 };
	int dy[4] = { 1, 0, -1, 0 };
	if (!bigConfiguration) // first configuration, first linkPosition is always in center
	{
		m_connectionPoints.push_back({ foundation.first, foundation.second });

		m_connectionPoints.push_back({ foundation.first + dx[pylonRotation % 4],
			foundation.second + dy[pylonRotation % 4] });
	}
	else // second configuration, first linkPos is up and second is down
	{
		m_connectionPoints.push_back({ foundation.first + dx[pylonRotation % 4],
			foundation.second + dy[pylonRotation % 4] });

		m_connectionPoints.push_back({ foundation.first + dx[(pylonRotation + 2) % 4],
			foundation.second + dy[(pylonRotation + 2) % 4] });
	}
}

CrossPylon::CrossPylon(const CrossPylon& other) :
	Pylon{ other }
{}

bool CrossPylon::canAddBridge(const Position& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);

	if (itFoundation != m_connectionPoints.end())
		return true;
	return false;
}

bool CrossPylon::addBridge(nonstd::observer_ptr<Bridge> bridge, const Position& foundation)
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);
	if (itFoundation != m_connectionPoints.end())
	{
		m_connections.emplace_back(bridge);
		return true;
	}
	return false;
}

void CrossPylon::removeBridge(nonstd::observer_ptr<Bridge> bridge)
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
}
