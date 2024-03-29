#pragma once

//#include "SinglePylon.h"
//#include "CrossPylon.h"
//#include "SquarePylon.h"
#include "Foundation.h"
#include "HumanPlayer.h"
#include <map>
#include <random>
#include <unordered_set>
#include <queue>
#include "observer_ptr.h"
#include "Utilities.h"

namespace twixt
{

	class Board
	{
	public:
		Board(uint8_t = 24, uint8_t mines = 12);
		Board(const Board&);
		Board& operator=(const Board&);
		~Board() = default;

		std::vector<std::vector<Foundation>>& getBoard();
		std::unordered_map<Position, std::unique_ptr<Pylon>>& getPylons();
		std::unordered_set<std::unique_ptr<Bridge>>& getBridges();
		uint8_t getSize() const;
		uint8_t getTotalMines() const;

		void setBoard(const std::vector<std::vector<Foundation>>&);
		void setPylons(const std::unordered_map<Position, std::unique_ptr<Pylon>>&);
		void setBridges(const std::unordered_set<std::unique_ptr<Bridge>>&);
		void setSize(uint8_t);
		void setTotalMines(uint8_t);

		void addPylon(Foundation&, Pylon::Color, Pylon::Type, uint8_t, bool);
		void addBridge(Foundation&, Foundation&, Pylon::Color);
		void removePylon(const Position&);
		void removeBridge(const nonstd::observer_ptr<Bridge>&);

		void spawnMines();
		bool addMine(const Position& pos);

		Foundation& operator[](const Position&);
		const Foundation& operator[](const Position&) const;

		Foundation& getFoundation(const Position&);
	
		bool verifyWinner(const Pylon::Color & color);
	private:
		uint8_t m_size;
		uint8_t m_totalMines;

		std::vector<std::vector<Foundation>> m_board;
		std::unordered_map<Position, std::unique_ptr<Pylon>> m_pylons;
		std::unordered_set<std::unique_ptr<Bridge>> m_bridges; //TO DO: change Bridge* to unique_ptr

		bool winnerFoundation(const Foundation&, uint8_t, Pylon::Color) const; //TO DO: fix memory access
																			   //violation for cross and square pylons on edge
		bool checkWinningRoute(std::queue<nonstd::observer_ptr<Pylon>>&, std::unordered_set<nonstd::observer_ptr<Pylon>>&, bool);//TO DO: fix memory access
																						 //violation for cross and square pylons on edge
	};
}