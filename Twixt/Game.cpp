#include "Game.h"

using namespace twixt;

Game::Game(uint8_t boardSize, uint8_t minesNumber) :
	m_board{ Board(boardSize, minesNumber) }, m_bob{ DebuilderBob(m_board) }
{
	m_reusableMinedFoundation
		= m_bigPylons = m_minedFundations
		= m_debuilderBob = m_cards = m_explodeArea = m_explodeCol = m_explodeRow = m_humanPlayers = false;

	m_explodeSingleLocation = true;

	m_player1 = std::make_unique<HumanPlayer>();
	m_player2 = std::make_unique<HumanPlayer>();

	m_boardSize = boardSize;
	m_areaLength = 1;
	m_currentPlayer = nonstd::make_observer<IPlayer>(m_player1.get());
	m_round = 0;
}

Game::Game(const Game& other) :
	m_board{ other.m_board },
	m_bob{ DebuilderBob(m_board) }
{
	m_humanPlayers = other.m_humanPlayers;
	m_reusableMinedFoundation = other.m_reusableMinedFoundation;
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;
	m_areaLength = other.m_areaLength;
	m_explodeArea = other.m_explodeArea;
	m_explodeCol = other.m_explodeCol;
	m_explodeRow = other.m_explodeRow;
	m_explodeSingleLocation = other.m_explodeSingleLocation;
	m_boardSize = other.m_boardSize;
	m_round = other.m_round;
}

Game& Game::operator=(const Game& other)
{
	m_humanPlayers = other.m_humanPlayers;
	m_reusableMinedFoundation = other.m_reusableMinedFoundation;
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;
	m_areaLength = other.m_areaLength;
	m_boardSize = other.m_boardSize;
	m_bob = other.m_bob;
	m_round = other.m_round;
	return *this;
}

void twixt::Game::Run()
{
	/*nonstd::observer_ptr<IPlayer> currentPlayer = nonstd::make_observer(m_player1.get());
	nonstd::observer_ptr<IPlayer> nextPlayer = nonstd::make_observer(m_player2.get());

	nextPlayer->setColor(Pylon::Color::Black);

	currentPlayer->setName("R");
	nextPlayer->setName("B");

	Position red = { 1,3 };
	Position black = { 0, 0 };

	if(m_debuilderBob)
		moveBob();
	while (true)
	{
		std::system("cls");
		printBoard();

		bool keepRound = processTurn(currentPlayer->getNextMove(), currentPlayer);

		if (m_board.verifyWinner(currentPlayer->getColor()))
		{
			printBoard();
			std::cout << currentPlayer->getName() << " won\n";
			return;
		}

		if (!keepRound)
		{
			std::swap(currentPlayer, nextPlayer);
			if (m_debuilderBob)
				moveBob();
		}
	}*/
}

void twixt::Game::setHumanPlayers(bool humanPlayers)
{
	m_humanPlayers = humanPlayers;
}

void Game::setBigPylons(bool bigPylons)
{
	m_bigPylons = bigPylons;
}

void Game::setMinedFoundations(bool minedFoundations)
{
	m_minedFundations = minedFoundations;
}

void Game::setExplodeSingleLocation(bool explodeSingleLocation)
{
	m_explodeSingleLocation = explodeSingleLocation;
}

void Game::setExplodeCol(bool explodeCol)
{
	m_explodeCol = explodeCol;
}

void Game::setExplodeRow(bool explodeRow)
{
	m_explodeRow = explodeRow;
}

void Game::setExplodeArea(bool explodeArea)
{
	m_explodeArea = explodeArea;
}

void Game::setReusableMinedFoundation(bool reusableMinedFoundation)
{
	m_reusableMinedFoundation = reusableMinedFoundation;
}

void Game::setDebuilderBob(bool debuilderBob)
{
	m_debuilderBob = debuilderBob;

	if (m_debuilderBob)
		m_bob = DebuilderBob(m_board);
}

void Game::setCards(bool cards)
{
	m_cards = cards;
}

//void Game::setPlayer1(const nonstd::observer_ptr<IPlayer>& player)
//{
//	m_player1 = std::make_unique<IPlayer>(player->getName());
//}

void twixt::Game::setPlayer1(const std::string& name, bool aiPlayer)
{
	m_player1.release();
	if (!aiPlayer)
		m_player1 = std::make_unique<HumanPlayer>(name);
	m_player1->setColor(twixt::Pylon::Color::Red);
}

//void Game::setPlayer2(const nonstd::observer_ptr<IPlayer>& player)
//{
//	m_player2 = std::make_unique<IPlayer>(player->getName());
//}

void twixt::Game::setPlayer2(const std::string& name, bool aiPlayer)
{
	m_player2.release();
	if (!aiPlayer)
		m_player2 = std::make_unique<HumanPlayer>(name);
	m_player2->setColor(twixt::Pylon::Color::Black);
}

void twixt::Game::setCurrentPlayer(const nonstd::observer_ptr<IPlayer>& currentPlayer)
{
	m_currentPlayer.reset(currentPlayer.get());
}

void Game::setBoard(const Board& board)
{
	m_board = board;
}

void twixt::Game::setCardDeck(const std::vector<Card>& cardDeck)
{
	m_cardDeck = cardDeck;
}

void twixt::Game::setCardStack(const std::stack<Card>& cardStack)
{
	m_cardStack = cardStack;
}

void twixt::Game::setRound(uint8_t round)
{
	m_round = round;
}

void twixt::Game::swapPlayers()
{
	if (m_currentPlayer->getColor() == Pylon::Color::Black)
	{
		m_currentPlayer = nonstd::make_observer<IPlayer>(m_player1.get());
		std::swap(m_player1, m_player2);
	}
}

bool twixt::Game::getHumanPlayers() const
{
	return m_humanPlayers;
}

bool Game::getBigPylons() const
{
	return m_bigPylons;
}

bool Game::getMinedFoundations() const
{
	return m_minedFundations;
}

bool Game::getExplodeSingleLocation() const
{
	return m_explodeSingleLocation;
}

bool Game::getExplodeCol() const
{
	return m_explodeCol;
}

bool Game::getExplodeRow() const
{
	return m_explodeRow;
}

bool Game::getExplodeArea() const
{
	return m_explodeArea;
}

bool Game::getReusableMinedFoundation() const
{
	return m_reusableMinedFoundation;
}

bool Game::getDebuilderBob() const
{
	return m_debuilderBob;
}

std::unique_ptr<IPlayer>& Game::getPlayer1()
{
	return m_player1;
}

std::unique_ptr<IPlayer>& Game::getPlayer2()
{
	return m_player2;
}

nonstd::observer_ptr<IPlayer>& twixt::Game::getCurrentPlayer()
{
	return m_currentPlayer;
}

Board& Game::getBoard()
{
	return m_board;
}

std::vector<Card> twixt::Game::getCardDeck() const
{
	return m_cardDeck;
}

std::stack<Card> twixt::Game::getCardStack() const
{
	return m_cardStack;
}

DebuilderBob& twixt::Game::getBob()
{
	return m_bob;
}

uint8_t twixt::Game::getRound() const
{
	return m_round;
}

bool Game::addPylon(const Position& pos, Pylon::Type type, Pylon::Color color, uint8_t pylonRotation, bool bigConfiguration)
{
	const auto& [row, col] = pos;
	switch (type)
	{
	case Pylon::Type::Single:
		if (validFoundation(pos, color) && m_currentPlayer->getNoPylons1x1() > 0)
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type, pylonRotation, bigConfiguration);
			m_currentPlayer->decrementPylon1x1();
			return true;
		}
		break;
	case Pylon::Type::Square:
		if (validFoundation(pos, color) &&
			validFoundation({ row,col + 1 }, color) &&
			validFoundation({ row + 1, col }, color) &&
			validFoundation({ row + 1, col + 1 }, color) && m_currentPlayer->getNoPylons2x2() > 0)
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type, pylonRotation, bigConfiguration);
			m_currentPlayer->decrementPylon2x2();
			return true;
		}
		break;
	case Pylon::Type::Cross:
		if (validFoundation(pos, color) &&
			validFoundation({ row + 1, col }, color) &&
			validFoundation({ row - 1, col }, color) &&
			validFoundation({ row, col + 1 }, color) &&
			validFoundation({ row, col - 1 }, color) && m_currentPlayer->getNoPylonsCross() > 0)
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type, pylonRotation, bigConfiguration);
			m_currentPlayer->decrementPylonCross();
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

bool Game::addBridge(const Position& startPoint, const Position& endPoint, Pylon::Color color)
{
	nonstd::observer_ptr<Pylon> startPylon = m_board.getFoundation(startPoint).getPylon();
	nonstd::observer_ptr<Pylon> endPylon = m_board.getFoundation(endPoint).getPylon();

	if (startPylon->getColor() != color || endPylon->getColor() != color)
		return false;

	if (startPylon == nullptr || endPylon == nullptr)
	{
		return false;
	}

	if (startPylon->getColor() != endPylon->getColor())
	{
		return false;
	}

	uint8_t dX = abs((int8_t)startPoint.first - (int8_t)endPoint.first),
		dY = abs((int8_t)startPoint.second - (int8_t)endPoint.second);

	if ((dX == 1 && dY == 2) || (dX == 2 && dY == 1))
	{
		if (startPylon->canAddBridge(startPoint) && endPylon->canAddBridge(endPoint))
		{
			for (auto& bridge : m_board.getBridges())
			{
				if (bridge->getPosStart() == startPoint &&
					bridge->getPosEnd() == endPoint)
				{
					return false;
				}

				if (bridge->getPosStart() == endPoint &&
					bridge->getPosEnd() == startPoint)
				{
					return false;
				}

				if (overlappingBridges(startPoint, endPoint, bridge->getPosStart(), bridge->getPosEnd()))
					return false;
			}
			m_board.addBridge(m_board.getFoundation(startPoint), m_board.getFoundation(endPoint), startPylon->getColor());
			m_currentPlayer->decrementBridge();
			return true;
		}
	}
	return false;
}

bool twixt::Game::placingPylonOnMine(const Position& position, Pylon::Type type)
{
	const auto& [x, y] = position;

	switch (type)
	{
	case twixt::Pylon::Type::Single:
		if (m_board[{x, y}].getMined())
			return true;

		break;
	case twixt::Pylon::Type::Square:
		if (m_board[{x, y}].getMined()
			|| m_board[{x + 1, y}].getMined()
			|| m_board[{x + 1, y + 1}].getMined()
			|| m_board[{x, y + 1}].getMined())
			return true;

		break;
	case twixt::Pylon::Type::Cross:
		if (m_board[{x, y}].getMined()
			|| m_board[{x + 1, y}].getMined()
			|| m_board[{x - 1, y }].getMined()
			|| m_board[{x, y + 1}].getMined()
			|| m_board[{x, y - 1}].getMined())
			return true;

		break;
	default:
		break;
	}

	return false;
}

twixt::Game::GameStatus twixt::Game::getCurrentGameStatus(Pylon::Color currentPlayerColor)
{
	//verify for draw
	if (!m_player1->getNoPylons1x1() && !m_player2->getNoPylons1x1())
	{
		if (m_bigPylons)
		{
			if (!m_player1->getNoPylons2x2() && !m_player2->getNoPylons2x2()
				&& !m_player1->getNoPylonsCross() && !m_player2->getNoPylonsCross())
				return GameStatus::Draw;
		}
		else
		{
			return GameStatus::Draw;
		}
	}

	//verify if current player won
	if (m_board.verifyWinner(currentPlayerColor))
		return GameStatus::Won;

	return GameStatus::None;
}

void Game::moveBob(const std::optional<Position>& position)
{
	m_bob.moveToNext(position);
}

void Game::printBoard()
{
	std::vector<std::vector<std::string>> boardMatrix(m_board.getSize(), std::vector<std::string>(m_board.getSize()));

	for (uint8_t i = 0; i < boardMatrix.size(); ++i)
	{
		for (uint8_t j = 0; j < boardMatrix[0].size(); ++j)
		{
			nonstd::observer_ptr<Pylon> element = m_board.getBoard()[i][j].getPylon();
			bool hasBob = m_board.getBoard()[i][j].getBob();
			bool elementMined = m_board.getBoard()[i][j].getMined();
			bool elementExploded = m_board.getBoard()[i][j].getExploded();
			if (element == nullptr)
			{
				boardMatrix[i][j] = ".";
			}
			else if (element->getColor() == Pylon::Color::Black)
			{
				boardMatrix[i][j] = "B";
			}
			else
			{
				boardMatrix[i][j] = "R";
			}
			if (elementMined)
			{
				boardMatrix[i][j] = "m";
			}
			if (hasBob)
			{
				boardMatrix[i][j] = "X";
			}
			if (elementExploded)
			{
				boardMatrix[i][j] = "E";
			}
		}
	}

	for (auto& bridge : m_board.getBridges())
	{
		Position positionStart = bridge->getPosStart(), positionEnd = bridge->getPosEnd();
		if (bridge->getPylonEnd()->getColor() == Pylon::Color::Red)
		{
			boardMatrix[positionStart.first][positionStart.second] = "r";
			boardMatrix[positionEnd.first][positionEnd.second] = "r";
		}
		else
		{
			boardMatrix[positionStart.first][positionStart.second] = "b";
			boardMatrix[positionEnd.first][positionEnd.second] = "b";
		}
	}

	for (auto& line : boardMatrix)
	{
		for (auto& element : line)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
}

void twixt::Game::printDeck(nonstd::observer_ptr<IPlayer> player)
{
	std::cout << std::endl;
	for (const auto& card : player->getCards())
		std::cout << card.getTargetString() << ' ' << card.getEffectString() << std::endl;
	std::cout << std::endl;
}

bool Game::removeBridge(const Position& start, const Position& end, Pylon::Color color)
{
	nonstd::observer_ptr<Bridge> bridgeToRemove = nullptr;

	for (const auto& bridge : m_board.getBridges())
	{
		if (bridge->getPosStart() == start && bridge->getPosEnd() == end)
		{
			bridgeToRemove = nonstd::make_observer(bridge.get());
			break;
		}
		if (bridge->getPosStart() == end && bridge->getPosEnd() == start)
		{
			bridgeToRemove = nonstd::make_observer(bridge.get());
			break;
		}
	}

	if (!bridgeToRemove || bridgeToRemove->getPylonStart()->getColor() != color)
		return false;

	m_board.removeBridge(bridgeToRemove);
	m_currentPlayer->incrementBridge();
	return true;
}

bool twixt::Game::removePylon(const Position& position, Pylon::Color color)
{
	nonstd::observer_ptr<Pylon> pylon = m_board[position].getPylon();
	if (pylon == nullptr || pylon->getColor() != color)
		return false;

	m_board.removePylon(position);
	return true;
}

bool twixt::Game::drawCard(const nonstd::observer_ptr<IPlayer>& player)
{
	if (m_cardStack.empty())
		return false;
	player->draw(m_cardStack);
	return true;
}

void twixt::Game::drawMultipleCards(const nonstd::observer_ptr<IPlayer>& player, uint8_t count)
{
	for (size_t i = 0; i < count; ++i)
		drawCard(player);
}

void twixt::Game::enemyLoseCards(const nonstd::observer_ptr<IPlayer>& currentPlayer, uint8_t count)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	nonstd::observer_ptr<IPlayer> enemy = nonstd::make_observer<IPlayer>(m_player1.get());

	if (currentPlayer == enemy)
		enemy = nonstd::make_observer<IPlayer>(m_player2.get());

	while (count > 0 && !enemy->getCards().empty())
	{
		std::uniform_int_distribution<> distrib(0, enemy->getCards().size() - 1);
		size_t index = distrib(gen);

		enemy->removeCard(index);
	}
}

bool twixt::Game::removeEnemyPylon(const Position& pos, const nonstd::observer_ptr<IPlayer>& currentPlayer)
{
	Pylon::Color enemyColor;
	if (currentPlayer->getColor() == Pylon::Color::Red)
		enemyColor = Pylon::Color::Black;
	else
		enemyColor = Pylon::Color::Red;

	return removePylon(pos, enemyColor);
}

bool twixt::Game::removeEnemyBridge(const Position& startPos, const Position& endPos, const nonstd::observer_ptr<IPlayer>& currentPlayer)
{
	Pylon::Color enemyColor;
	if (currentPlayer->getColor() == Pylon::Color::Red)
		enemyColor = Pylon::Color::Black;
	else
		enemyColor = Pylon::Color::Red;

	return removeBridge(startPos, endPos, enemyColor);
}

bool twixt::Game::placeBiggerPylon(const nonstd::observer_ptr<IPlayer>& currentPlayer, const Position& pos, Pylon::Type type, Pylon::Color color,
	uint8_t pylonRotation, bool bigConfiguration)
{
	if (type == Pylon::Type::Cross)
	{
		currentPlayer->incrementPylonCross(); //if this player has 0 available pylons, they should be able to place one if they use a card
		if (!addPylon(pos, type, color, pylonRotation, bigConfiguration))
		{
			currentPlayer->decrementPylonCross();
			return false; //no cross pylon could be placed so repeat
		}

		return true;
	}

	currentPlayer->incrementPylon2x2();
	if (!addPylon(pos, type, color, pylonRotation, bigConfiguration))
	{
		currentPlayer->decrementPylon2x2();
		return false; //no square pylon could be placed so repeat
	}

	return true;
}

bool twixt::Game::placeMine(const Position& pos)
{
	if (m_board[pos].getPylon() == nullptr)
	{
		m_board[pos].setMined(true);
		return true;
	}

	return false;
}



bool twixt::Game::overlappingBridges(const Position& bridge1Start, const Position& bridge1End, const Position& bridge2Start, const Position& bridge2End) const
{
	if (bridge1Start == bridge2Start || bridge1End == bridge2End || bridge1Start == bridge2End || bridge2Start == bridge1End) return false;
	return counterclockwiseOrder(bridge1Start, bridge2Start, bridge2End) != counterclockwiseOrder(bridge1End, bridge2Start, bridge2End) &&
		counterclockwiseOrder(bridge1Start, bridge1End, bridge2Start) != counterclockwiseOrder(bridge1Start, bridge1End, bridge2End);
}

bool Game::validFoundation(const Position& pos, Pylon::Color color)
{
	switch (color)
	{
	case Pylon::Color::Red:
		if (!(0 <= pos.first && pos.first < m_board.getBoard().size() &&
			1 <= pos.second && pos.second < m_board.getBoard().size() - 1 &&
			m_board.getBoard()[pos.first][pos.second].getPylon() == nullptr))
			return false;
		break;
	case Pylon::Color::Black:
		if (!(1 <= pos.first && pos.first < m_board.getBoard().size() - 1 &&
			0 <= pos.second && pos.second < m_board.getBoard().size() &&
			m_board.getBoard()[pos.first][pos.second].getPylon() == nullptr))
			return false;
		break;
	}

	if (!verifyMinedFoundation(pos))
		return false;

	if (m_board[pos].getBob())
		return false;

	return true;
}

bool Game::verifyMinedFoundation(const Position& pos)
{
	Foundation& foundation = m_board.getBoard()[pos.first][pos.second];

	if (!foundation.getMined() && !foundation.getExploded())
	{
		return true;
	}

	if (!foundation.getExploded())
	{
		explodePylons(pos);
		return false;  //if it gets here it means that the player placed a pylon
		//on a mine, so their turn should skip
	}
	else if (m_reusableMinedFoundation)
	{
		return true;
	}

	return false;
}

void Game::explodePylons(const Position& pos)
{
	if (m_explodeSingleLocation)
	{
		explodeSingleLocation(pos);
	}
	if (m_explodeCol)
	{
		explodeCol(pos);
	}
	if (m_explodeRow)
	{
		explodeRow(pos);
	}
	if (m_explodeArea)
	{
		explodeArea(pos);
	}
}

void Game::explodeSingleLocation(const Position& pos)
{
	Foundation& foundation = m_board.getBoard()[pos.first][pos.second];
	foundation.setMined(false);
	foundation.setExploded(true);
}

void Game::explodeCol(const Position& pos)
{
	for (size_t indexBoard = 0; indexBoard < m_board.getSize(); ++indexBoard)
	{
		Foundation& foundation = m_board.getBoard()[pos.first][indexBoard];
		if (foundation.getPylon())
		{
			m_board.removePylon({ pos.first, indexBoard });
		}
		foundation.setMined(false);
		foundation.setExploded(true);
	}
}

void Game::explodeRow(const Position& pos)
{
	for (size_t indexBoard = 0; indexBoard < m_board.getSize(); ++indexBoard)
	{
		Foundation& foundation = m_board.getBoard()[indexBoard][pos.second];
		if (foundation.getPylon())
		{
			m_board.removePylon({ indexBoard, pos.second });
		}
		foundation.setMined(false);
		foundation.setExploded(true);
	}
}

void Game::explodeArea(const Position& pos)
{
	auto& [rowPos, colPos] = pos;
	for (size_t indexRowBoard = std::max(rowPos - m_areaLength, 0); indexRowBoard < std::min(rowPos + m_areaLength + 1, (int)m_board.getSize()); ++indexRowBoard)
	{
		for (size_t indexColBoard = std::max(colPos - m_areaLength, 0); indexColBoard < std::min(colPos + m_areaLength + 1, (int)m_board.getSize()); ++indexColBoard)
		{
			Foundation& foundation = m_board.getBoard()[indexRowBoard][indexColBoard];
			if (foundation.getPylon())
			{
				m_board.removePylon({ indexRowBoard, indexColBoard });
			}
			foundation.setMined(false);
			foundation.setExploded(true);
		}
	}
}

//bool twixt::Game::processTurn(const IPlayer::Move& nextMove, const nonstd::observer_ptr<IPlayer>& currentPlayer)
//{
//	if (!currentPlayer->validMove(nextMove, m_boardSize))
//	{
//		return true; //bad move, another chance
//	}
//	const auto& [action, pos1, pos2] = nextMove;
//
//	switch (action)
//	{
//		case IPlayer::Action::AddSinglePylon:
//			if (!addPylon(pos1.value(), Pylon::Type::Single, currentPlayer->getColor()))
//				return true; //pylon couldn't be placed, so the player gets another chance
//			return false;
//		case IPlayer::Action::AddSquarePylon:
//			if (!addPylon(pos1.value(), Pylon::Type::Square, currentPlayer->getColor()))
//				return true;
//			return false;
//		case IPlayer::Action::AddCrossPylon:
//			if (!addPylon(pos1.value(), Pylon::Type::Cross, currentPlayer->getColor()))
//				return true;
//			return false;
//		case IPlayer::Action::AddBridge:
//			addBridge(pos1.value(), pos2.value(), currentPlayer->getColor());
//			return true;
//		case IPlayer::Action::RemovePylon:
//			if (!removePylon(pos1.value(), currentPlayer->getColor()))
//				return true;
//			return false;
//		case IPlayer::Action::RemoveBridge:
//			removeBridge(pos1.value(), pos2.value(), currentPlayer->getColor());
//			return true;
//		case IPlayer::Action::DrawCard:
//			drawCard(currentPlayer);
//			return true;
//	}
//}

bool Game::getCards() const
{
	return m_cards;
}
