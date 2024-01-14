#pragma once

#include "Board.h"
#include "HumanPlayer.h"
#include "DebuilderBob.h"
#include "../ObserverPtr/observer_ptr.h"
#include <array>
#include <iostream>
#include <fstream>

namespace twixt
{
	class Game
	{
	public:
		enum class GameStatus {
			None,
			Won,
			Draw
		};

		Game(uint8_t = 24, uint8_t = 12);
		Game(const Game&);
		Game& operator=(const Game&) = delete;
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
		void setCurrentPlayer(const nonstd::observer_ptr<IPlayer>&);
		void setBoard(const Board&);
		void setCardDeck(const std::vector<Card>&);
		void setCardStack(const std::stack<Card>&);
		void setDeckSize(uint8_t);
		void setRound(uint8_t);
		void swapPlayers();

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
		uint8_t getDeckSize() const;
		std::unique_ptr<IPlayer>& getPlayer1();//TO DO: change to observer ptr
		std::unique_ptr<IPlayer>& getPlayer2();
		nonstd::observer_ptr<IPlayer>& getCurrentPlayer();
		Board& getBoard();
		std::vector<Card> getCardDeck() const;
		std::stack<Card> getCardStack() const;
		DebuilderBob& getBob();
		uint8_t getRound() const;

		bool addPylon(const Position&, Pylon::Type, Pylon::Color, uint8_t pylonRotation, bool bigConfiguration = true); //both square and cross pylons have 2 possible configurations
		bool addBridge(const Position&, const Position&, Pylon::Color);
		bool placingPylonOnMine(const Position&, Pylon::Type);

		GameStatus getCurrentGameStatus(Pylon::Color);

		//cards
		void shuffleDeck();
		bool drawCard();
		void drawMultipleCards(uint8_t);
		void enemyLoseCards(uint8_t);

		bool removeEnemyPylon(const Position&);
		bool removeEnemyBridge(const Position&, const Position&);

		bool placeBiggerPylon(const Position&, Pylon::Type, Pylon::Color, uint8_t pylonRotation, bool bigConfiguration = true);
		bool placeMine(const Position&, bool = false); //it shouldn't allow for placing mines under pylons

		void moveBob(const std::optional<Position>& = std::nullopt);

		void moveBobCard(const std::optional<Position>&);

		void printBoard();
		void printDeck(nonstd::observer_ptr<IPlayer> player);


		bool removeBridge(const Position&, const Position&, Pylon::Color);
		bool removePylon(const Position&, Pylon::Color);

		void saveGame(const std::string&);
		void loadGame(const std::string&);

		void addCardsToDeck();
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
		nonstd::observer_ptr<IPlayer> m_currentPlayer;
		Board m_board;
		uint8_t m_areaLength;
		uint8_t m_boardSize;
		uint8_t m_round;
		uint8_t m_deckSize;
		DebuilderBob m_bob;
		std::vector<Card> m_cardDeck;
		std::stack<Card> m_cardStack;
		std::unordered_map<Card::Effect, std::string> m_cardEffects;


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
	};
}
