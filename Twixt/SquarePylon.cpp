#include "SquarePylon.h"

using namespace twixt;

SquarePylon::SquarePylon(const Position& foundation, Color color, Type type, uint8_t pylonRotation, bool bigConfiguration) :
	Pylon{ foundation, color, type, pylonRotation, bigConfiguration }
{
	int dx[4] = { 0, 0, 1, 1 };
	int dy[4] = {0, 1, 1, 0};

	if (bigConfiguration) //both links are on the same side
	{
		m_connectionPoints.push_back({ foundation.first + dx[pylonRotation % 4],
			foundation.second + dy[pylonRotation % 4] });

		m_connectionPoints.push_back({ foundation.first + dx[(pylonRotation + 1) % 4],
			foundation.second + dy[(pylonRotation + 1) % 4] });
	}
	else
	{
		m_connectionPoints.push_back({ foundation.first + dx[pylonRotation % 4],
			foundation.second + dy[pylonRotation % 4] });

		m_connectionPoints.push_back({ foundation.first + dx[(pylonRotation + 2) % 4],
			foundation.second + dy[(pylonRotation + 2) % 4] });
	}
}

SquarePylon::SquarePylon(const SquarePylon& other) :
	Pylon{ other }
{}

bool SquarePylon::canAddBridge(const Position& foundation) const
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);

	if (itFoundation != m_connectionPoints.end())
		return true;
	return false;
}

bool SquarePylon::addBridge(nonstd::observer_ptr<Bridge> bridge, const Position& foundation)
{
	auto itFoundation = std::find(m_connectionPoints.begin(), m_connectionPoints.end(), foundation);
	
	if (itFoundation != m_connectionPoints.end()) {
		m_connections.emplace_back(bridge);
		return true;
	}
	return false;
}

void SquarePylon::removeBridge(nonstd::observer_ptr<Bridge> bridge)
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
