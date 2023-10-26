#pragma once

#include <utility>
#include "Pylon.h"

class Bridge
{
private:
	Pylon* m_pylonStart;
	Pylon* m_pylonEnd;
	std::pair<uint8_t, uint8_t> m_posStart;
	std::pair<uint8_t, uint8_t> m_posEnd;

public:
	Bridge();
	Bridge(Pylon*, Pylon*, const std::pair<uint8_t, uint8_t>&, const std::pair<uint8_t, uint8_t>&);
	Bridge(const Bridge&);
	Bridge& operator=(const Bridge&);
	~Bridge() = default;
};

