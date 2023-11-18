#pragma once

//#include "SinglePylon.h"
//#include "CrossPylon.h"
//#include "SquarePylon.h"
#include "Foundation.h"
#include "Player.h"
#include <map>
#include <random>
#include <unordered_set>
#include <queue>

using Position = std::pair<uint8_t, uint8_t>;

class Board
{
public:
	Board(uint8_t = 24, uint8_t mines = 0);
	Board(const Board&);
	Board& operator=(const Board&);
	~Board();

	std::vector<std::vector<Foundation>>& getBoard();
	std::map<Position, Pylon*> getPylons() const;
	std::multimap<Pylon*, Bridge*> getBridges() const;
	uint8_t getSize() const;
	uint8_t getTotalMines() const;

	void setBoard(const std::vector<std::vector<Foundation>>&);
	void setPylons(const std::map<Position, Pylon*>&);
	void setBridges(const std::multimap<Pylon*, Bridge*>&);
	void setSize(uint8_t);
	void setTotalMines(uint8_t);
	
	void addPylon(Foundation&, Pylon::Color, Pylon::Type);
	void addBridge(Foundation&, Foundation&, Pylon::Color);

	void spawnMines();

	Foundation& operator[](const Position&);
	const Foundation& operator[](const Position&) const;

	Foundation& getFoundation(const Position&);
private:
	uint8_t m_size;
	uint8_t m_totalMines;

	std::vector<std::vector<Foundation>> m_board;
	std::map<Position, Pylon*> m_pylons;
	std::multimap<Pylon*, Bridge*> m_bridges;

	bool winnerFoundation(const Foundation&, uint8_t, Pylon::Color) const;
	bool checkWinningRoute(std::queue<Pylon*>&, std::unordered_set<Pylon*>&, bool);
	bool verifyWinner(const Player&);
};

