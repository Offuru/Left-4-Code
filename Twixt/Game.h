#pragma once

#include "Board.h"
#include "HumanPlayer.h"
#include "DebuilderBob.h"
//#include "observer_ptr.h"
#include "observer_ptr.h"
#include <array>
#include <iostream>

namespace twixt
{
	class Game
	{
	public:

		Game(uint8_t = 24, uint8_t = 12);
		Game(const Game&);
		Game& operator=(const Game&);
		~Game() = default;

		void Run(); //TO DO: modularize function
					//player must place a pylon every turn
					//player place one/multiple bridges or none at all


		void setHumanPlayers(bool);
		void setBigPylons(bool);
		void setMinedFoundations(bool);
		void setExplodeSingleLocation(bool);
		void setExplodeCol(bool);
		void setExplodeRow(bool);
		void setExplodeArea(bool);
		void setReusableMinedFoundation(bool);
		void setDebuilderBob(bool);
		void setCards(bool);
		void setPlayer1(const nonstd::observer_ptr<IPlayer>&);
		void setPlayer1(const std::string&, bool aiPlayer = false);
		void setPlayer2(const nonstd::observer_ptr<IPlayer>&);
		void setPlayer2(const std::string&, bool aiPlayer = false);
		void setBoard(const Board&);
		void setCardDeck(const std::vector<Card>&);
		void setCardStack(const std::stack<Card>&);

		bool getHumanPlayers() const;
		bool getBigPylons() const;
		bool getMinedFoundations() const;
		bool getExplodeSingleLocation() const;
		bool getExplodeCol() const;
		bool getExplodeRow() const;
		bool getExplodeArea() const;
		bool getReusableMinedFoundation() const;
		bool getDebuilderBob() const;
		bool getCards() const;
		std::unique_ptr<IPlayer>& getPlayer1();//TO DO: change to observer ptr
		std::unique_ptr<IPlayer>& getPlayer2();
		Board& getBoard();
		std::vector<Card> getCardDeck() const;
		std::stack<Card> getCardStack() const;

		bool addPylon(const Position&, Pylon::Type, Pylon::Color, uint8_t pylonRotation, bool bigConfiguration = true); //both square and cross pylons have 2 possible configurations
		bool addBridge(const Position&, const Position&, Pylon::Color);

		bool removeBridge(const Position&, const Position&, Pylon::Color);
		bool removePylon(const Position&, Pylon::Color);

		bool drawCard(const nonstd::observer_ptr<IPlayer>&);//TO DO: change to IPlayer shared_ptr later

		void moveBob();
		void printBoard();
		void printDeck(nonstd::observer_ptr<IPlayer> player);

	private:

		bool m_humanPlayers;
		bool m_bigPylons;
		bool m_minedFundations;
		bool m_explodeSingleLocation;
		bool m_explodeCol;
		bool m_explodeRow;
		bool m_explodeArea;
		bool m_reusableMinedFoundation;
		bool m_debuilderBob;
		bool m_cards; //TO DO: change to flag bitset
		std::unique_ptr<IPlayer> m_player1;//TO DO: change to IPlayer* to allow for human/ai players
		std::unique_ptr<IPlayer> m_player2;
		Board m_board;
		uint8_t m_areaLength;
		uint8_t m_boardSize;
		DebuilderBob m_bob;
		std::vector<Card> m_cardDeck;
		std::stack<Card> m_cardStack;

		bool overlappingBridges(const Position&, const Position&, const Position&, const Position&) const;
		bool validFoundation(const Position&, Pylon::Color);
		bool verifyMinedFoundation(const Position&);
		void explodePylons(const Position&);
		void explodeSingleLocation(const Position&);
		void explodeCol(const Position&);
		void explodeRow(const Position&);
		void explodeArea(const Position&);
		//bool processTurn(const IPlayer::Move&, const nonstd::observer_ptr<IPlayer>&); //it returns true only if the player
																//changed their bridges, so they can
																//modify more of them in the same round,
																//and returns false if a pylon was added/deleted
																//so the round skips

		Position getPlayerPosInput() const;

		bool draw2Cards(nonstd::observer_ptr<IPlayer> target);
		bool removeOpponentCard(nonstd::observer_ptr<IPlayer> target);
		bool removePylon(nonstd::observer_ptr<IPlayer> target);
		bool removeBridge(nonstd::observer_ptr<IPlayer> target);
		bool place2Pylons(nonstd::observer_ptr<IPlayer> target, uint8_t pylonRotation, bool bigConfiguration);
		bool placeBigPylon(nonstd::observer_ptr<IPlayer> target, Pylon::Type type, uint8_t pylonRotation, bool bigConfiguration);
		bool moveBobCard();
		bool placeMine();

		bool playCard(const Card& card);
	};
}
