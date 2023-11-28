#pragma once
#include "Board.h"
#include "HumanPlayer.h"
#include "DebuilderBob.h"
#include <array>
#include <iostream>

namespace twixt
{
	class Game
	{
	public:

		Game(uint8_t = 24);
		Game(const Game&);
		Game& operator=(const Game&);
		~Game() = default;

		void Run(); //TO DO: modularize function
					//player must place a pylon every turn
					//player place one/multiple bridges or none at all
					

		void setBigPylons(bool);
		void setMinedFoundations(bool);
		void setExplodeSingleLocation(bool);
		void setExplodeCol(bool);
		void setExplodeRow(bool);
		void setExplodeArea(bool);
		void setReusableMinedFoundation(bool);
		void setDebuilderBob(bool);
		void setCards(bool);
		void setPlayer1(const HumanPlayer&);
		void setPlayer2(const HumanPlayer&);
		void setBoard(const Board&);

		bool getBigPylons() const;
		bool getMinedFoundations() const;
		bool getExplodeSingleLocation() const;
		bool getExplodeCol() const;
		bool getExplodeRow() const;
		bool getExplodeArea() const;
		bool getReusableMinedFoundation() const;
		bool getDebuilderBob() const;
		bool getCards() const;
		HumanPlayer getPlayer1() const;
		HumanPlayer getPlayer2() const;
		Board& getBoard();

		bool addPylon(const Position&, Pylon::Type, Pylon::Color);
		bool addBridge(const Position&, const Position&, Pylon::Color);

		bool removeBridge(const Position&, const Position&);

		void moveBob();
		void printBoard();

	private:

		DebuilderBob m_bob;
		bool m_bigPylons;
		bool m_minedFundations;
		bool m_explodeSingleLocation;
		bool m_explodeCol;
		bool m_explodeRow;
		bool m_explodeArea;
		bool m_reusableMinedFoundation;
		bool m_debuilderBob;
		bool m_cards; //TO DO: change to flag bitset
		HumanPlayer m_player1;//TO DO: change to IPlayer* to allow for human/ai players
		HumanPlayer m_player2;
		Board m_board;
		uint8_t m_areaLength;
		uint8_t m_boardSize;

		bool validFoundation(const Position&, Pylon::Color);
		bool verifyMinedFoundation(const Position&);
		void explodePylons(const Position&);
		void explodeSingleLocation(const Position&);
		void explodeCol(const Position&);
		void explodeRow(const Position&);
		void explodeArea(const Position&);
	};
}
