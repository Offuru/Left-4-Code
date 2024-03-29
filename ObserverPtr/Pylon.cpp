#include "Pylon.h"

using namespace twixt;

Pylon::Pylon(const Position& foundation, Color color, Type type, uint8_t pylonRotation, bool bigConfiguration) :
	m_color{ color }, m_connections{ std::vector<nonstd::observer_ptr<Bridge>>() },
	m_connectionPoints{ std::vector<Position>() },
	m_type{ type },
	m_pylonRotation{pylonRotation},
	m_bigConfiguration{bigConfiguration}
{}

Pylon::Pylon(const Pylon& other) :
	m_color{ other.m_color }, m_connectionPoints{ other.m_connectionPoints },
	m_foundations{ other.m_foundations }, m_connections{ other.m_connections },
	m_type{ other.m_type },
	m_pylonRotation{ other.m_pylonRotation },
	m_bigConfiguration{ other.m_bigConfiguration }
{}

Pylon& Pylon::operator=(const Pylon& other)
{
	m_type = other.m_type;
	m_color = other.m_color;
	m_pylonRotation = other.m_pylonRotation;
	m_bigConfiguration = other.m_bigConfiguration;
	
	m_connectionPoints = other.m_connectionPoints;
	m_foundations = other.m_foundations;
	m_connections = other.m_connections;

	return *this;
}

std::vector<Position> Pylon::getFoundations() const
{
	return m_foundations;
}

std::vector<nonstd::observer_ptr<Bridge>> Pylon::getConnections() const
{
	return m_connections;
}

std::vector<Position> Pylon::getConnectionPoints() const
{
	return m_connectionPoints;
}

Pylon::Color Pylon::getColor() const
{
	return m_color;
}

Pylon::Type Pylon::getType() const
{
	return m_type;
}

bool twixt::Pylon::getPylonRotation() const
{
	return m_pylonRotation;
}

uint8_t twixt::Pylon::getBigConfiguration() const
{
	return m_bigConfiguration;
}

void Pylon::setFoundations(const std::vector<Position>& foundations)
{
	m_foundations = foundations;
}

void Pylon::setConnections(const std::vector<nonstd::observer_ptr<Bridge>>& connections)
{
	m_connections = connections;
}

void Pylon::setConnectionPoints(const std::vector<Position>& connectionPoints)
{
	m_connectionPoints = connectionPoints;
}

void Pylon::setColor(const Color& color)
{
	m_color = color;
}

void twixt::Pylon::setBigConfiguration(const uint8_t& bigConfiguration)
{
	m_bigConfiguration = bigConfiguration;
}

void Pylon::addFoundation(const Position& foundation)
{
	m_foundations.emplace_back(foundation);
}
