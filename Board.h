#pragma once

#include "Foundation.h"
#include <map>


class Board
{
public:
	Board();
	Board(const Board&);
	Board& operator=(const Board&);
	
	~Board();
private:
	const uint8_t m_size = 24;

	std::vector<std::vector<Foundation>> m_board;
	std::map<std::pair<uint8_t, uint8_t>, Pylon*> m_pylons;
	std::multimap<Pylon*, Bridge*> m_bridges;
};

