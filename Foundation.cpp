#include "Foundation.h"

Foundation::Foundation() :
	m_position{ std::make_pair(0,0) }, m_mined{ false }, m_pylon{ nullptr } {};

Foundation::Foundation(std::pair<uint8_t, uint8_t> position, bool mined, Pylon* pylon) :
	m_position{ position }, m_mined{ mined }, m_pylon{ pylon } {};

Foundation::Foundation(const Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	m_pylon = other.m_pylon;//Multiple foundations ca point to the same pylon (2x2 & cross pylons)
}

Foundation& Foundation::operator=(const Foundation& other)
{
	m_position = other.m_position;
	m_mined = other.m_mined;
	m_pylon = other.m_pylon;

	return *this;
}

Foundation::~Foundation()
{
	if(m_pylon)
		delete m_pylon;
}
