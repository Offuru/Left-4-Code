#include "Game.h"

Game::Game()
{
	m_reusableMinedFoundation
		= m_bigPylons = m_minedFundations
		= m_debuilderBob = m_cards = false;
	m_player1 = Player();
	m_player2 = Player();
	m_player2.setColor(Pylon::Color::Black);
	m_board = Board();
}

Game::Game(const Game& other)
{
	m_reusableMinedFoundation = other.m_reusableMinedFoundation;
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;
}

Game& Game::operator=(const Game& other)
{
	m_reusableMinedFoundation = other.m_reusableMinedFoundation;
	m_bigPylons = other.m_bigPylons;
	m_minedFundations = other.m_minedFundations;
	m_debuilderBob = other.m_debuilderBob;
	m_cards = other.m_cards;

	return *this;
}

void Game::setBigPylons(bool bigPylons)
{
	m_bigPylons = bigPylons;
}

void Game::setMinedFoundations(bool minedFoundations)
{
	m_minedFundations = minedFoundations;
}

void Game::setReusableMinedFoundation(bool reusableMinedFoundation)
{
	m_reusableMinedFoundation = reusableMinedFoundation;
}

void Game::setDebuilderBob(bool debuilderBob)
{
	m_debuilderBob = debuilderBob;
}

void Game::setCards(bool cards)
{
	m_cards = cards;
}

void Game::setPlayer1(const Player& player)
{
	m_player1 = player;
}

void Game::setPlayer2(const Player& player)
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

bool Game::getReusableMinedFoundation() const
{
	return m_reusableMinedFoundation;
}

bool Game::getDebuilderBob() const
{
	return m_debuilderBob;
}

Player Game::getPlayer1() const
{
	return m_player1;
}

Player Game::getPlayer2() const
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

bool Game::addBridge(const Position& startPoint, const Position& endPoint)
{
	Pylon* startPylon = m_board.getFoundation(startPoint).getPylon();
	Pylon* endPylon = m_board.getFoundation(endPoint).getPylon();

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
	std::vector<std::vector<std::string>> boardMatrix(24, std::vector<std::string>(24));

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

	if (!verifyMinedFoundation(pos, color))
		return false;

	if (m_board[pos].getBob())
		return false;

	return true;
}

bool Game::verifyMinedFoundation(const Position& pos, Pylon::Color color)
{
	Foundation& foundation = m_board.getBoard()[pos.first][pos.second];

	if (!foundation.getMined() && !foundation.getExploded())
	{
		return true;
	}

	if (!foundation.getExploded())
	{
		explodePylons(pos, color);
		return false;
	} 
	else if (m_reusableMinedFoundation)
	{
		return true;
	}

	return false;
}

void Game::explodePylons(const Position& pos, Pylon::Color color)
{}

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

bool Game::getCards() const
{
	return m_cards;
}
