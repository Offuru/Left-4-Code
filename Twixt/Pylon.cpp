#include "Pylon.h"

Pylon::Pylon(const Foundation& foundation, Color color) :
	m_position{ foundation }, m_color{ color }, m_connections{ std::vector<std::reference_wrapper<const Bridge>>() },
	m_connectionPoints{ std::vector<std::pair<uint8_t,uint8_t>>() } {};

Pylon::Pylon(const Pylon& other) :
	m_position{ other.m_position }, m_color{ other.m_color }, m_connections{ other.m_connections }, m_connectionPoints{ other.m_connectionPoints } {};

Pylon& Pylon::operator=(const Pylon& other)
{
	m_position = other.m_position;
	m_color = other.m_color;
	m_connections = other.m_connections;

	m_connectionPoints = other.m_connectionPoints;
	return *this;
}

const Foundation& Pylon::getPosition() const
{
	return m_position;
}

std::vector<std::reference_wrapper<const Bridge>> Pylon::getConnections() const
{
	return m_connections;
}

std::vector<std::pair<uint8_t, uint8_t>> Pylon::getConnectionPoints() const
{
	return m_connectionPoints;
}

Pylon::Color Pylon::getColor() const
{
	return m_color;
}

void Pylon::setFoundation(const Foundation& position)
{
	m_position = position;
}

void Pylon::setConnections(const std::vector<std::reference_wrapper<const Bridge>>& connections)
{
	m_connections = connections;
}

void Pylon::setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>& connectionPoints)
{
	m_connectionPoints = connectionPoints;
}

void Pylon::setColor(const Color& color)
{
	m_color = color;
}
