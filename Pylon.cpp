#include "Pylon.h"

Pylon::Pylon() :
	m_position{ nullptr }, m_color{ Color::Red }, m_connections{ std::vector<Bridge*>() },
	m_connectionPoints{ std::vector<std::pair<uint8_t,uint8_t>>() } {};

Pylon::Pylon(Foundation* foundation, Color color) :
	m_position{ foundation }, m_color{ color }, m_connections{ std::vector<Bridge*>() },
	m_connectionPoints{ std::vector<std::pair<uint8_t,uint8_t>>() } {};


Pylon::Pylon(const Pylon& other)
{
	m_position = other.m_position;
	m_color = other.m_color;
	m_connections.resize(other.m_connections.size(), nullptr);
	
	for (int i = 0; i < other.m_connections.size(); ++i)
	{
		m_connections[i] = new Bridge(*other.m_connections[i]);
	}
	m_connectionPoints = other.m_connectionPoints;
}

Pylon& Pylon::operator=(const Pylon& other)
{
	m_position = other.m_position;
	m_color = other.m_color;
	m_connections.resize(other.m_connections.size(), nullptr);

	for (int i = 0; i < other.m_connections.size(); ++i)
	{
		m_connections[i] = new Bridge(*other.m_connections[i]);
	}
	m_connectionPoints = other.m_connectionPoints;
	return *this;
}

Pylon::~Pylon()
{
	for(auto& it : m_connections)
	{
		delete it;
	}
}

Foundation* Pylon::getPosition() const
{
	return m_position;
}

std::vector<Bridge*> Pylon::getConnections() const
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

void Pylon::setFoundation(Foundation* other)
{
	m_position = other;
}

void Pylon::setConnections(const std::vector<Bridge*>& other)
{
	m_connections.resize(other.size(), nullptr);

	for (int i = 0; i < other.size(); ++i)
	{
		m_connections[i] = new Bridge(*other[i]);
	}
}

void Pylon::setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>& other)
{
	m_connectionPoints = other;
}

void Pylon::setColor(const Color& other)
{
	m_color = other;
}
