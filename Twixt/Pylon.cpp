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
		if(it != nullptr)
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

void Pylon::setFoundation(Foundation* position)
{
	m_position = position;
}

void Pylon::setConnections(const std::vector<Bridge*>& connections)
{
	m_connections.resize(connections.size(), nullptr);

	for (int i = 0; i < connections.size(); ++i)
	{
		m_connections[i] = new Bridge(*connections[i]);
	}
}

void Pylon::setConnectionPoints(const std::vector<std::pair<uint8_t, uint8_t>>& connectionPoints)
{
	m_connectionPoints = connectionPoints;
}

void Pylon::setColor(const Color& color)
{
	m_color = color;
}
