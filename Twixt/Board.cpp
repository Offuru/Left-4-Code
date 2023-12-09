#include "Board.h"
#include <iostream>
#include <memory>
using namespace twixt;

Board::Board(uint8_t size, uint8_t mines) :
	m_size{ size }, m_totalMines{ mines }
{
	Foundation p;
	m_board.resize(m_size);
	for (int i = 0; i < m_size; ++i)
	{
		m_board[i].resize(m_size);
		for (int j = 0; j < m_size; ++j)
		{
			Foundation p = Foundation(std::make_pair(i, j), false, nullptr);
			m_board[i][j] = p;
		}
	}
}

Board::Board(const Board& other) :
	m_board{ other.m_board }, m_size{ other.m_size }, m_totalMines{ other.m_totalMines }
{
	for (const auto& [position, pylon] : other.m_pylons)
	{
		SinglePylon* single = dynamic_cast<SinglePylon*>(pylon.get());
		if (single)
		{
			m_pylons.insert({ position,
				std::make_shared<SinglePylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
		SquarePylon* square = dynamic_cast<SquarePylon*>(pylon.get());
		if (square)
		{
			m_pylons.insert({ position,
				std::make_shared<SquarePylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
		CrossPylon* cross = dynamic_cast<CrossPylon*>(pylon.get());
		if (cross)
		{
			m_pylons.insert({ position,
				std::make_shared<CrossPylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
	}

	for (const auto& [pylon, bridge] : other.m_bridges)
	{
		auto whichPylon = m_pylons.find(pylon->getFoundations()[0]);

		if (whichPylon != m_pylons.end())
		{
			std::shared_ptr<Bridge> newBridge(new Bridge(*bridge));
			m_bridges.insert({ whichPylon->second, newBridge });
			//pylon* from bridge shouldn't get modified
		}
	}
}

Board& Board::operator=(const Board& other)
{
	if (this == &other)
		return *this;

	for (const auto& [position, pylon] : other.m_pylons)
	{
		SinglePylon* single = dynamic_cast<SinglePylon*>(pylon.get());
		if (single)
		{
			m_pylons.insert({ position,
				std::make_shared<SinglePylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
		SquarePylon* square = dynamic_cast<SquarePylon*>(pylon.get());
		if (square)
		{
			m_pylons.insert({ position,
				std::make_shared<SquarePylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
		CrossPylon* cross = dynamic_cast<CrossPylon*>(pylon.get());
		if (cross)
		{
			m_pylons.insert({ position,
				std::make_shared<CrossPylon>(pylon->getFoundations().at(0),pylon->getColor(),pylon->getType()) });
			continue;
		}
	}

	for (const auto& [pylon, bridge] : other.m_bridges)
	{
		auto whichPylon = m_pylons.find(pylon->getFoundations()[0]);

		if (whichPylon != m_pylons.end())
		{
			std::shared_ptr<Bridge> newBridge(new Bridge(*bridge));
			m_bridges.insert({ whichPylon->second, newBridge });
			//pylon* from bridge shouldn't get modified
		}
	}

	return *this;
}

Board::~Board()
{
	//
}

std::vector<std::vector<Foundation>>& Board::getBoard()
{
	return m_board;
}

std::unordered_map<Position, std::shared_ptr<Pylon>>& Board::getPylons()
{
	return m_pylons;
}

std::multimap<std::shared_ptr<Pylon>, std::shared_ptr<Bridge>> Board::getBridges() const
{
	return m_bridges;
}

uint8_t Board::getSize() const
{
	return m_size;
}

uint8_t Board::getTotalMines() const
{
	return m_totalMines;
}

void Board::setBoard(const std::vector<std::vector<Foundation>>& board)
{
	m_board = board;
}

void Board::setPylons(const std::unordered_map<Position, std::shared_ptr<Pylon>>& pylons)
{
	for (const auto& it : pylons)
		addPylon(m_board[it.second->getFoundations().at(0).first][it.second->getFoundations().at(0).second],
			it.second->getColor(), it.second->getType());
}

void Board::setBridges(const std::multimap<std::shared_ptr<Pylon>, std::shared_ptr<Bridge>>& bridges)
{
	m_bridges = bridges;
}

void Board::setSize(uint8_t size)
{
	m_size = size;
}

void Board::setTotalMines(uint8_t totalMines)
{
	m_totalMines = totalMines;
}

void Board::addPylon(Foundation& foundation, Pylon::Color color, Pylon::Type type)
{
	std::shared_ptr<Pylon> pylon = nullptr;

	const auto& [x, y] = foundation.getPosition();
	switch (type)
	{
	case Pylon::Type::Single:
		pylon = std::make_shared<SinglePylon>(foundation.getPosition(), color, type);
		pylon->addFoundation({ x, y });

		foundation.setPylon(pylon);
		break;

	case Pylon::Type::Square:
		pylon = std::make_unique<SquarePylon>(foundation.getPosition(), color, type);
		pylon->addFoundation({ x, y });
		pylon->addFoundation({ x + 1, y });
		pylon->addFoundation({ x + 1, y + 1 });
		pylon->addFoundation({ x, y + 1 });

		foundation.setPylon(pylon);
		m_board[x + 1][y].setPylon(pylon);
		m_board[x + 1][y + 1].setPylon(pylon);
		m_board[x][y + 1].setPylon(pylon);
		break;

	case Pylon::Type::Cross:
		pylon = std::make_unique<CrossPylon>(foundation.getPosition(), color, type);
		pylon->addFoundation({ x, y });
		pylon->addFoundation({ x + 1, y });
		pylon->addFoundation({ x - 1, y });
		pylon->addFoundation({ x, y + 1 });
		pylon->addFoundation({ x, y - 1 });

		foundation.setPylon(pylon);
		m_board[x + 1][y].setPylon(pylon);
		m_board[x - 1][y].setPylon(pylon);
		m_board[x][y + 1].setPylon(pylon);
		m_board[x][y - 1].setPylon(pylon);
		break;

	default:
		break;
	}

	m_pylons[foundation.getPosition()].swap(pylon);
}

void Board::addBridge(Foundation& foundation1, Foundation& foundation2, Pylon::Color color)
{
	std::shared_ptr<Bridge> bridge(new Bridge(foundation1.getPylon(), foundation2.getPylon(), foundation1.getPosition(), foundation2.getPosition()));

	foundation1.getPylon()->addBridge(bridge, foundation1.getPosition());
	foundation2.getPylon()->addBridge(bridge, foundation2.getPosition());
	m_bridges.insert(std::make_pair(foundation1.getPylon(), bridge));
}

void Board::removePylon(const Position& position)
{
	std::shared_ptr<Pylon> currPylon = m_board[position.first][position.second].getPylon();
	if (currPylon == nullptr)
		return;

	//delete bridges
	for (auto& bridge : currPylon->getConnections())
	{
		if (bridge->getPylonStart() != currPylon)
		{
			bridge->getPylonStart()->removeBridge(bridge);
		}
		else
		{
			bridge->getPylonEnd()->removeBridge(bridge);
		}
		auto range = m_bridges.equal_range(bridge->getPylonStart());
		bool removedBridge = false;
		for (auto it = range.first; it != range.second; ++it)
		{
			if (it->second == bridge)
			{
				m_bridges.erase(it);
				removedBridge = true;
				break;
			}
		}
		if (!removedBridge)
		{
			range = m_bridges.equal_range(bridge->getPylonEnd());
			for (auto it = range.first; it != range.second; ++it)
			{
				if (it->second == bridge)
				{
					m_bridges.erase(it);
					break;
				}
			}
		}
		bridge.reset();
	}

	for (auto& [posX, posY] : currPylon->getFoundations())
	{
		m_board[posX][posY].setPylon(nullptr);
	}

	for (const auto& it : m_pylons)
	{
		if (it.second == currPylon)
		{
			m_pylons.erase(it.first);
			break;
		}
	}

}

void Board::removeBridge(std::shared_ptr<Bridge> bridge)
{
	for (auto it = m_bridges.begin(); it != m_bridges.end(); ++it)
	{
		if (it->second == bridge)
		{
			it->second->getPylonEnd()->removeBridge(bridge);
			it->second->getPylonStart()->removeBridge(bridge);
			m_bridges.erase(it);

			return;
		}
	}
}

void Board::spawnMines()
{
	int numMines = 0;
	std::random_device rd;
	std::mt19937 eng(rd());
	while (numMines < m_totalMines)
	{
		std::uniform_int_distribution<> distrRow(0, m_board.size() - 1);
		std::uniform_int_distribution<> distrCol(0, m_board.size() - 1);
		uint8_t rowPos = distrRow(eng);
		uint8_t colPos = distrCol(eng);

		if (m_board[rowPos][colPos].getMined() == false)
		{
			m_board[rowPos][colPos].setMined(true);
			++numMines;
		}
	}
}

Foundation& Board::operator[](const Position& position)
{
	return const_cast<Foundation&>(std::as_const(*this)[position]);
}

const Foundation& Board::operator[](const Position& position) const
{
	auto& [row, column] = position;

	if (row < 0 || column < 0 || row >= m_size || column >= m_size)
		throw std::out_of_range("Position out of bounds");

	return m_board[row][column];
}

Foundation& Board::getFoundation(const Position& pos)
{
	return m_board[pos.first][pos.second];
}

bool Board::winnerFoundation(const Foundation& foundation, uint8_t rule, Pylon::Color color) const
{
	//verify if the current Pylon occupies foundations near/on end line of board
	//winning if foundation is on the edge of the board or edge - 1
	if (color == Pylon::Color::Red && (foundation.getPosition().first == rule ||
		foundation.getPosition().first == rule + 1))
		return true;

	if (color == Pylon::Color::Black && (foundation.getPosition().second == rule ||
		foundation.getPosition().second == rule + 1))
		return true;

	return false;
}

bool Board::checkWinningRoute(std::queue<std::shared_ptr<Pylon>>& nextVisit, std::unordered_set<std::shared_ptr<Pylon>>& visited, bool firstRun = true)
{
	//firstRun == true means that the current route starts from the left side (for red) or
	//from the above (for black)
	uint8_t currRuleForWinning = 0;
	if (firstRun)
		currRuleForWinning = m_size - 2;

	while (!nextVisit.empty())
	{
		std::shared_ptr<Pylon> currPylon = nextVisit.front();
		nextVisit.pop();

		if (visited.find(currPylon) == visited.end())
		{
			for (const auto& bridge : (*currPylon).getConnections())
			{
				std::shared_ptr<Pylon> nextPylon = bridge->getPylonEnd();

				if (nextPylon == currPylon)
					nextPylon = bridge->getPylonStart();

				nextVisit.emplace(nextPylon);
			}

			visited.insert(currPylon);
		}

		//verify if currPylon stands on winning pos

		for (const auto& pos : currPylon->getFoundations())
		{
			if (winnerFoundation(pos, currRuleForWinning, currPylon->getColor()))
				return true;
		}
	}

	return false;
}

bool Board::verifyWinner(const HumanPlayer& player)
{
	std::queue<std::shared_ptr<Pylon>> nextVisit;
	std::unordered_set<std::shared_ptr<Pylon>> visited;

	for (int i = 0; i < m_board.size(); ++i)
	{
		std::shared_ptr<Pylon> currPylon;
		if (player.getColor() == Pylon::Color::Red)
			currPylon = m_board[0][i].getPylon();
		else
			currPylon = m_board[i][0].getPylon();

		if (currPylon != nullptr)
		{
			nextVisit.emplace(currPylon);
		}
	}

	if (checkWinningRoute(nextVisit, visited, true))
	{
		return true;
	}

	for (int i = 0; i < m_board.size(); ++i)
	{
		std::shared_ptr<Pylon> currPylon;
		if (player.getColor() == Pylon::Color::Red)
			currPylon = m_board[m_size - 1][i].getPylon();
		else
			currPylon = m_board[i][m_size - 1].getPylon();

		if (currPylon != nullptr)
		{
			nextVisit.emplace(currPylon);
		}
	}

	if (checkWinningRoute(nextVisit, visited, false))
	{
		return true;
	}


	return false;
}


