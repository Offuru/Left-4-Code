#pragma once

#include "SinglePylon.h"
#include "CrossPylon.h"
#include "SquarePylon.h"
#include "Foundation.h"
#include "Player.h"
#include <map>
#include <unordered_set>
#include <queue>

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
	
	void addPylon(Foundation&, Pylon::Color, Pylon::Type);
	void addBridge(const Foundation&, const Foundation&, Pylon::Color);

private:
	const uint8_t m_size = 24;

	std::vector<std::vector<Foundation>> m_board;
	std::map<std::pair<uint8_t, uint8_t>, Pylon*> m_pylons;
	std::multimap<Pylon*, Bridge*> m_bridges;

	bool winnerFoundation(const Foundation&, uint8_t, Pylon::Color) const;
	bool checkWinningRoute(std::queue<Pylon*>&, std::unordered_set<Pylon*>&, bool);
	bool verifyWinner(const Player&);
};

