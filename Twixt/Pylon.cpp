#include "Pylon.h"

Pylon::Pylon(const Foundation& foundation, Color color) :
	m_color{ color }, m_connections{ std::vector<Bridge*>() },
	m_connectionPoints{ std::vector<std::pair<uint8_t,uint8_t>>() } 
{
	m_foundations.emplace_back(foundation);
}

std::vector<std::reference_wrapper<const Foundation>> Pylon::getFoundations() const
{
	return m_foundations;
}

std::vector<Bridge*> Pylon::getConnections() const
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

void Pylon::setFoundations(const std::vector<std::reference_wrapper<const Foundation>>& foundations)
{
	m_foundations = foundations;
}

void Pylon::setConnections(const std::vector<Bridge*>& connections)
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

void Pylon::addFoundation(const Foundation& foundation)
{
	m_foundations.emplace_back(foundation);
}
