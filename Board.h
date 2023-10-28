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

	std::vector<std::vector<Foundation>> getBoard() const;
	std::map<std::pair<uint8_t, uint8_t>, Pylon*> getPylons() const;
	std::multimap<Pylon*, Bridge*> getBridges() const;

	void setBoard(const std::vector<std::vector<Foundation>>&);
	void setPylons(const std::map<std::pair<uint8_t, uint8_t>, Pylon*>&);
	void setBridges(const std::multimap<Pylon*, Bridge*>&);

private:
	const uint8_t m_size = 24;

	std::vector<std::vector<Foundation>> m_board;
	std::map<std::pair<uint8_t, uint8_t>, Pylon*> m_pylons;
	std::multimap<Pylon*, Bridge*> m_bridges;
};

