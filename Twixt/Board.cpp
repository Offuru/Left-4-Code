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
	m_size{ other.m_size }, m_totalMines{ other.m_totalMines }
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

	for (const auto& [position, pylon] : other.m_pylons)
	{
		addPylon(m_board[position.first][position.second], pylon->getColor(), pylon->getType(), pylon->getPylonRotation(), pylon->getBigConfiguration());
	}

	for (auto& bridge : other.m_bridges)
	{
		const auto& [x1, y1] = bridge->getPosStart();
		const auto& [x2, y2] = bridge->getPosEnd();


		addBridge(m_board[x1][y1], m_board[x2][y2], bridge->getPylonStart()->getColor());
	}
}

Board& Board::operator=(const Board& other)
{
	if (this == &other)
		return *this;

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

	for (const auto& [position, pylon] : other.m_pylons)
	{
		addPylon(m_board[position.first][position.second], pylon->getColor(), pylon->getType(), pylon->getPylonRotation(), pylon->getBigConfiguration());
	}

	for (auto& bridge : other.m_bridges)
	{
		const auto& [x1, y1] = bridge->getPosStart();
		const auto& [x2, y2] = bridge->getPosEnd();


		addBridge(m_board[x1][y1], m_board[x2][y2], bridge->getPylonStart()->getColor());
	}

	return *this;
}

std::vector<std::vector<Foundation>>& Board::getBoard()
{
	return m_board;
}

std::unordered_map<Position, std::unique_ptr<Pylon>>& Board::getPylons()
{
	return m_pylons;
}

std::unordered_set<std::unique_ptr<Bridge>>& Board::getBridges()
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

void Board::setPylons(const std::unordered_map<Position, std::unique_ptr<Pylon>>& pylons)
{
	for (const auto& it : pylons)
		addPylon(m_board[it.second->getFoundations().at(0).first][it.second->getFoundations().at(0).second],
			it.second->getColor(), it.second->getType(), it.second->getPylonRotation(), it.second->getBigConfiguration());
}

void Board::setBridges(const std::unordered_set<std::unique_ptr<Bridge>>& bridges)
{
	for (const auto& bridge : m_bridges)
	{
		m_bridges.emplace(std::make_unique<Bridge>(bridge->getPylonStart(), bridge->getPylonEnd(), bridge->getPosStart(), bridge->getPosEnd()));
	}
}

void Board::setSize(uint8_t size)
{
	m_size = size;
	Foundation p;
	m_board = std::vector<std::vector<Foundation>>();
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

void Board::setTotalMines(uint8_t totalMines)
{
	m_totalMines = totalMines;
}

void Board::addPylon(Foundation& foundation, Pylon::Color color, Pylon::Type type, uint8_t pylonRotation, bool bigConfiguration)
{
	std::unique_ptr<Pylon> pylon;

	const auto& [x, y] = foundation.getPosition();
	switch (type)
	{
	case Pylon::Type::Single:
		pylon = std::make_unique<SinglePylon>(foundation.getPosition(), color, type, pylonRotation, bigConfiguration);
		pylon->addFoundation({ x, y });

		foundation.setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		break;

	case Pylon::Type::Square:
		pylon = std::make_unique<SquarePylon>(foundation.getPosition(), color, type, pylonRotation, bigConfiguration);
		pylon->addFoundation({ x, y });
		pylon->addFoundation({ x + 1, y });
		pylon->addFoundation({ x + 1, y + 1 });
		pylon->addFoundation({ x, y + 1 });

		foundation.setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x + 1][y].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x + 1][y + 1].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x][y + 1].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		break;

	case Pylon::Type::Cross:
		pylon = std::make_unique<CrossPylon>(foundation.getPosition(), color, type, pylonRotation, bigConfiguration);
		pylon->addFoundation({ x, y });
		pylon->addFoundation({ x + 1, y });
		pylon->addFoundation({ x - 1, y });
		pylon->addFoundation({ x, y + 1 });
		pylon->addFoundation({ x, y - 1 });

		foundation.setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x + 1][y].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x - 1][y].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x][y + 1].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		m_board[x][y - 1].setPylon(nonstd::make_observer<Pylon>(pylon.get()));
		break;

	default:
		break;
	}

	m_pylons[foundation.getPosition()].swap(pylon);
}

void Board::addBridge(Foundation& foundation1, Foundation& foundation2, Pylon::Color color)
{
	auto it = m_bridges.emplace(std::make_unique<Bridge>(foundation1.getPylon(), foundation2.getPylon(), foundation1.getPosition(), foundation2.getPosition()));

	auto bridge = it.first->get();

	foundation1.getPylon()->addBridge(nonstd::make_observer<Bridge>(bridge), foundation1.getPosition());
	foundation2.getPylon()->addBridge(nonstd::make_observer<Bridge>(bridge), foundation2.getPosition());
}

void Board::removePylon(const Position& position)
{
	nonstd::observer_ptr<Pylon> currPylon = m_board[position.first][position.second].getPylon();
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

		for (auto& board_bridge : m_bridges)
		{
			if (board_bridge.get() == bridge.get())
			{
				m_bridges.erase(board_bridge);
				break;
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
		if (it.second.get() == currPylon.get())
		{
			m_pylons.erase(it.first);
			break;
		}
	}

}

void Board::removeBridge(const nonstd::observer_ptr<Bridge>& bridge)
{
	bridge->getPylonEnd()->removeBridge(nonstd::make_observer(bridge.get()));
	bridge->getPylonStart()->removeBridge(nonstd::make_observer(bridge.get()));
	for (const auto& boardBridge : m_bridges)
	{
		if (boardBridge.get() == bridge.get())
		{
			m_bridges.erase(boardBridge);
			break;
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

bool twixt::Board::addMine(const Position& pos)
{
	Foundation& foundation = (*this)[pos];

	if (foundation.getMined() == true)
		return false;

	foundation.setMined(true);
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

bool Board::checkWinningRoute(std::queue<nonstd::observer_ptr<Pylon>>& nextVisit, std::unordered_set<nonstd::observer_ptr<Pylon>>& visited, bool firstRun = true)
{
	//firstRun == true means that the current route starts from the left side (for red) or
	//from the above (for black)
	uint8_t currRuleForWinning = 0;
	if (firstRun)
		currRuleForWinning = m_size - 2;

	while (!nextVisit.empty())
	{
		nonstd::observer_ptr<Pylon> currPylon = nextVisit.front();
		nextVisit.pop();

		if (visited.find(currPylon) == visited.end())
		{
			for (const auto& bridge : (*currPylon).getConnections())
			{
				nonstd::observer_ptr<Pylon> nextPylon = bridge->getPylonEnd();

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

bool Board::verifyWinner(const nonstd::observer_ptr<IPlayer>& player)
{
	std::queue<nonstd::observer_ptr<Pylon>> nextVisit;
	std::unordered_set<nonstd::observer_ptr<Pylon>> visited;

	for (int i = 0; i < m_board.size(); ++i)
	{
		nonstd::observer_ptr<Pylon> currPylon;
		if (player->getColor() == Pylon::Color::Red)
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
		nonstd::observer_ptr<Pylon> currPylon;
		if (player->getColor() == Pylon::Color::Red)
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


