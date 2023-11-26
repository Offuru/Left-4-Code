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
#include "Utilities.h"

namespace twixt
{

	class Board
	{
	public:
		Board(uint8_t = 24, uint8_t mines = 0);
		Board(const Board&);
		Board& operator=(const Board&);
		~Board();

		::std::vector<::std::vector<Foundation>>& getBoard();
		::std::unordered_map<Position, ::std::unique_ptr<Pylon>>& getPylons();
		::std::multimap<Pylon*, Bridge*> getBridges() const;
		uint8_t getSize() const;
		uint8_t getTotalMines() const;

		void setBoard(const ::std::vector<::std::vector<Foundation>>&);
		void setPylons(const ::std::unordered_map<Position, ::std::unique_ptr<Pylon>>&);
		void setBridges(const ::std::multimap<Pylon*, Bridge*>&);
		void setSize(uint8_t);
		void setTotalMines(uint8_t);

		void addPylon(Foundation&, Pylon::Color, Pylon::Type);
		void addBridge(Foundation&, Foundation&, Pylon::Color);
		void removePylon(const Position&);
		void removeBridge(Bridge*);

		void spawnMines();

		Foundation& operator[](const Position&);
		const Foundation& operator[](const Position&) const;

		Foundation& getFoundation(const Position&);

	private:
		uint8_t m_size;
		uint8_t m_totalMines;

		::std::vector<::std::vector<Foundation>> m_board;
		::std::unordered_map<Position, ::std::unique_ptr<Pylon>> m_pylons;
		::std::multimap<Pylon*, Bridge*> m_bridges;

		bool winnerFoundation(const Foundation&, uint8_t, Pylon::Color) const;
		bool checkWinningRoute(::std::queue<Pylon*>&, ::std::unordered_set<Pylon*>&, bool);
		bool verifyWinner(const Player&);
	};
}