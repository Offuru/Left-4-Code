#include "Bridge.h"

using namespace twixt;

Bridge::Bridge() :
	m_pylonStart{ nullptr }, m_pylonEnd{ nullptr }, m_posStart{ ::std::make_pair(0,0) }, m_posEnd{ ::std::make_pair(0,0) } {};

Bridge::Bridge(Pylon* pylonStart, Pylon* pylonEnd, const Position& posStart, const Position& posEnd) :
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

Position Bridge::getPosStart() const
{
	return m_posStart;
}

Position Bridge::getPosEnd() const
{
	return m_posEnd;
}

void Bridge::setPylonStart(Pylon* pylonStart)
{
	m_pylonStart = pylonStart;
}

void Bridge::setPylonEnd(Pylon* pylonEnd)
{
	m_pylonEnd = pylonEnd;
}

void Bridge::setPosStart(const Position& posStart)
{
	m_posStart = posStart;
}

void Bridge::setPosEnd(const Position& posEnd)
{
	m_posEnd = posEnd;
}
