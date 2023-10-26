#include "Bridge.h"

Bridge::Bridge() :
	m_pylonStart{ nullptr }, m_pylonEnd{ nullptr }, m_posStart{ std::make_pair(0,0) }, m_posEnd{ std::make_pair(0,0) } {};

Bridge::Bridge(Pylon* pylonStart, Pylon* pylonEnd, const std::pair<uint8_t, uint8_t>& posStart, const std::pair<uint8_t, uint8_t>& posEnd) :
	m_pylonStart{ pylonStart }, m_pylonEnd{ pylonEnd}, m_posStart{ posStart }, m_posEnd{ posEnd } {};

Bridge::Bridge(const Bridge& other)
{
	m_pylonStart = other.m_pylonStart;
	m_pylonEnd = other.m_pylonEnd;
	m_posStart = other.m_posStart;
	m_posEnd = other.m_posEnd;
}

Bridge& Bridge::operator=(const Bridge& other)
{
	m_pylonStart = other.m_pylonStart;
	m_pylonEnd = other.m_pylonEnd;
	m_posStart = other.m_posStart;
	m_posEnd = other.m_posEnd;

	return *this;
}

Pylon* Bridge::getPylonStart() const
{
	return m_pylonStart;
}

Pylon* Bridge::getPylonEnd() const
{
	return m_pylonEnd;
}

std::pair<uint8_t, uint8_t> Bridge::getPosStart() const
{
	return m_posStart;
}

std::pair<uint8_t, uint8_t> Bridge::getPosEnd() const
{
	return m_posEnd;
}

void Bridge::setPylonStart(Pylon* other)
{
	m_pylonStart = other;
}

void Bridge::setPylonEnd(Pylon* other)
{
	m_pylonEnd = other;
}

void Bridge::setPosStart(const std::pair<uint8_t, uint8_t>& other)
{
	m_posStart = other;
}

void Bridge::setPosEnd(const std::pair<uint8_t, uint8_t>& other)
{
	m_posEnd = other;
}
