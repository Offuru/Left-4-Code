#pragma once

#include <utility>
#include "Pylon.h"

class Pylon;

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

	Pylon* getPylonStart() const;
	Pylon* getPylonEnd() const;
	std::pair<uint8_t, uint8_t> getPosStart() const;
	std::pair<uint8_t, uint8_t> getPosEnd() const;

	void setPylonStart(Pylon*);
	void setPylonEnd(Pylon*);
	void setPosStart(const std::pair<uint8_t, uint8_t>&);
	void setPosEnd(const std::pair<uint8_t, uint8_t>&);
};

