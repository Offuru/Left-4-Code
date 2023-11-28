#include "Game.h"

using namespace twixt;

Game::Game(uint8_t boardSize) :
	m_board{ Board(boardSize) }
{
	m_reusableMinedFoundation
		= m_bigPylons = m_minedFundations
		= m_debuilderBob = m_cards = m_explodeArea = m_explodeCol = m_explodeRow = m_explodeSingleLocation = false;
	std::string name1, name2;

	std::cout << "Player 1 : ";
	std::cin >> name1;
	m_player1 = HumanPlayer(name1);
	m_player1.setColor(Pylon::Color::Red);

	std::cout << "Player 2 : ";
	std::cin >> name2;
	m_player2 = HumanPlayer(name2);
	m_player2.setColor(Pylon::Color::Black);

	m_boardSize = boardSize;
	m_areaLength = 2;
}

Game::Game(const Game& other)
{
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
}

Game& Game::operator=(const Game& other)
{
	m_reusableMinedFoundation = other.m_reusableMinedFoundation;
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;
	m_areaLength = other.m_areaLength;

	return *this;
}

void twixt::Game::Run()
{
	HumanPlayer currentPlayer = m_player1;
	HumanPlayer nextPlayer = m_player2;

	Position red = { 1,3 };
	Position black = { 0, 0 };

	while (true)
	{
		//moveBob();
		std::system("cls");
		printBoard();

		const auto& [action, pos1, pos2] = currentPlayer.getNextMove();
		switch (action)
		{
		case IPlayer::Action::AddSinglePylon:
			addPylon(pos1, Pylon::Type::Single, currentPlayer.getColor());
			break;
		case IPlayer::Action::AddSquarePylon:
			addPylon(pos1, Pylon::Type::Square, currentPlayer.getColor());
			break;
		case IPlayer::Action::AddCrossPylon:
			addPylon(pos1, Pylon::Type::Cross, currentPlayer.getColor());
			break;
		case IPlayer::Action::AddBridge:
			addBridge(pos1, pos2.value(), currentPlayer.getColor());
			break;
		case IPlayer::Action::RemovePylon:
			m_board.removePylon(pos1);
			break;
		case IPlayer::Action::RemoveBridge:
			removeBridge(pos1, pos2.value());
			break;
		default:
			break;
		}

		if (m_board.verifyWinner(currentPlayer))
		{
			printBoard();
			std::cout << currentPlayer.getName() << " won\n";
			return;
		}

		std::swap(currentPlayer, nextPlayer);
	}
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
		m_bob = DebuilderBob(m_boardSize);
}

void Game::setCards(bool cards)
{
	m_cards = cards;
}

void Game::setPlayer1(const HumanPlayer& player)
{
	m_player1 = player;
}

void Game::setPlayer2(const HumanPlayer& player)
{
	m_player2 = player;
}

void Game::setBoard(const Board& board)
{
	m_board = board;
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

HumanPlayer Game::getPlayer1() const
{
	return m_player1;
}

HumanPlayer Game::getPlayer2() const
{
	return m_player2;
}

Board& Game::getBoard()
{
	return m_board;
}

bool Game::addPylon(const Position& pos, Pylon::Type type, Pylon::Color color)
{
	const auto& [row, col] = pos;
	switch (type)
	{
	case Pylon::Type::Single:
		if (validFoundation(pos, color))
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type);
			return true;
		}
		break;
	case Pylon::Type::Square:
		if (validFoundation(pos, color) &&
			validFoundation({ row,col + 1 }, color) &&
			validFoundation({ row + 1, col }, color) &&
			validFoundation({ row + 1, col + 1 }, color))
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type);
			return true;
		}
		break;
	case Pylon::Type::Cross:
		if (validFoundation(pos, color) &&
			validFoundation({ row + 1, col }, color) &&
			validFoundation({ row - 1, col }, color) &&
			validFoundation({ row, col + 1 }, color) &&
			validFoundation({ row, col - 1 }, color))
		{
			m_board.addPylon(m_board.getFoundation(pos), color, type);
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
	Pylon* startPylon = m_board.getFoundation(startPoint).getPylon();
	Pylon* endPylon = m_board.getFoundation(endPoint).getPylon();

	if (startPylon->getColor() != color || startPylon->getColor() != color)
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
			for (auto& [pylon, bridge] : m_board.getBridges())
			{
				if (startPylon == pylon)
				{
					if (bridge->getPosStart() == startPoint &&
						bridge->getPosEnd() == endPoint)
					{
						return false;
					}
				}
				else if (endPylon == pylon)
				{
					if (bridge->getPosStart() == endPoint &&
						bridge->getPosEnd() == startPoint)
					{
						return false;
					}
				}
			}
			m_board.addBridge(m_board.getFoundation(startPoint), m_board.getFoundation(endPoint), startPylon->getColor());
			return true;
		}
	}
	return false;
}

void Game::moveBob()
{
	m_bob.moveToNext(m_board);
}

void Game::printBoard()
{
	std::vector<std::vector<std::string>> boardMatrix(m_board.getSize(), std::vector<std::string>(m_board.getSize()));

	for (uint8_t i = 0; i < boardMatrix.size(); ++i)
	{
		for (uint8_t j = 0; j < boardMatrix[0].size(); ++j)
		{
			Pylon* element = m_board.getBoard()[i][j].getPylon();
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

	for (auto& [pylon, bridge] : m_board.getBridges())
	{
		Position positionStart = bridge->getPosStart(), positionEnd = bridge->getPosEnd();
		if (pylon->getColor() == Pylon::Color::Red)
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

bool Game::removeBridge(const Position& start, const Position& end)
{
	Bridge* bridgeToRemove = nullptr;

	for (const auto& [pylon, bridge] : m_board.getBridges())
	{
		if (bridge->getPosStart() == start && bridge->getPosEnd() == end)
		{
			bridgeToRemove = bridge;
			break;
		}
		if (bridge->getPosStart() == end && bridge->getPosEnd() == start)
		{
			bridgeToRemove = bridge;
			break;
		}
	}

	if (!bridgeToRemove)
		return false;

	m_board.removeBridge(bridgeToRemove);
	return true;
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

	if (!verifyMinedFoundation(pos)) //TO DO: should be removed, @stdragos for more info
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
		return false;
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

bool Game::getCards() const
{
	return m_cards;
}
