#include "Board.h"

Board::Board()
{
	m_board.resize(m_size);
	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			m_board[i].emplace_back(Foundation(std::make_pair(i, j)));
		}
	}
}

Board::Board(const Board& other) :
	m_board{ other.m_board }, m_pylons{ other.m_pylons }, m_bridges{ other.m_bridges } {}

Board& Board::operator=(const Board& other)
{
	m_board = other.m_board;
	m_pylons = other.m_pylons;
	m_bridges = other.m_bridges;

	return *this;
}

Board::~Board()
{
	for (auto& line : m_board)
		for (auto& foundation : line)
			delete foundation.getPylon();
}

std::vector<std::vector<Foundation>> Board::getBoard() const
{
	return m_board;
}

std::map<Position, Pylon*> Board::getPylons() const
{
	return m_pylons;
}

std::multimap<Pylon*, Bridge*> Board::getBridges() const
{
	return m_bridges;
}

void Board::setBoard(const std::vector<std::vector<Foundation>>& board)
{
	m_board = board;
}

void Board::setPylons(const std::map<Position, Pylon*>& pylons)
{
	m_pylons = pylons;
}

void Board::setBridges(const std::multimap<Pylon*, Bridge*>& bridges)
{
	m_bridges = bridges;
}

void Board::addPylon(Foundation& foundation, Pylon::Color color, Pylon::Type type)
{
	Pylon* pylon;
	switch (type)
	{
	case Pylon::Type::Single:
		pylon = new SinglePylon(foundation, color);
		foundation.setPylon(pylon);
		break;

	case Pylon::Type::Square:
		pylon = new SquarePylon(foundation, color);
		foundation.setPylon(pylon);
		m_board[foundation.getPosition().first + 1][foundation.getPosition().second].setPylon(pylon);
		m_board[foundation.getPosition().first + 1][foundation.getPosition().second + 1].setPylon(pylon);
		m_board[foundation.getPosition().first][foundation.getPosition().second + 1].setPylon(pylon);
		break;
		
	case Pylon::Type::Cross:
		pylon = new CrossPylon(foundation, color);
		foundation.setPylon(pylon);
		m_board[foundation.getPosition().first + 1][foundation.getPosition().second].setPylon(pylon);
		m_board[foundation.getPosition().first - 1][foundation.getPosition().second].setPylon(pylon);
		m_board[foundation.getPosition().first][foundation.getPosition().second + 1].setPylon(pylon);
		m_board[foundation.getPosition().first][foundation.getPosition().second - 1].setPylon(pylon);
		break;

	default:
		break;
	}

	m_pylons.insert(std::make_pair(foundation.getPosition(), pylon));
}

void Board::addBridge(const Foundation& foundation1, const Foundation& foundation2, Pylon::Color color)
{
	if (foundation1.getPylon()->canAddBridge(foundation1) && foundation2.getPylon()->canAddBridge(foundation2))
	{
		Bridge* bridge = new Bridge(foundation1.getPylon(), foundation2.getPylon(), foundation1.getPosition(), foundation2.getPosition());

		foundation1.getPylon()->addBridge(bridge, foundation1);
		foundation2.getPylon()->addBridge(bridge, foundation2);
		m_bridges.insert(std::make_pair(foundation1.getPylon(), bridge));
	}
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

	if (color == Pylon::Color::Black && foundation.getPosition().second == rule ||
		foundation.getPosition().second == rule + 1)
		return true;

	return false;
}

bool Board::checkWinningRoute(std::queue<Pylon*>& nextVisit, std::unordered_set<Pylon*>& visited, bool firstRun = true)
{
	//firstRun == true means that the current route starts from the left side (for red) or
	//from the above (for black)
	uint8_t currRuleForWinning = 0;
	if (firstRun)
		currRuleForWinning = m_size - 2;

	while (!nextVisit.empty())
	{
		Pylon* currPylon = nextVisit.front();
		nextVisit.pop();

		if (visited.find(currPylon) == visited.end())
		{
			for (const auto& bridge : (*currPylon).getConnections())
			{
				Pylon* nextPylon = bridge->getPylonEnd();

				if (nextPylon == currPylon)
					nextPylon = bridge->getPylonStart();

				nextVisit.emplace(nextPylon);
			}

			visited.insert(currPylon);
		}

		//verify if currPylon stands on winning pos


		SinglePylon* single = dynamic_cast<SinglePylon*>(currPylon);
		if (single)
		{
			if (winnerFoundation(single->getFoundations()[0], currRuleForWinning, single->getColor()))
				return true;
		}
		CrossPylon* cross = dynamic_cast<CrossPylon*>(currPylon);
		if (cross)
		{
			for (const auto& pos : cross->getFoundations())
			{
				if (winnerFoundation(pos, currRuleForWinning, single->getColor()))
					return true;
			}
		}
		SquarePylon* square = dynamic_cast<SquarePylon*>(currPylon);
		if (square)
		{
			for (const auto& pos : square->getFoundations())
			{
				if (winnerFoundation(pos, currRuleForWinning, single->getColor()))
					return true;
			}
		}
	}

	return false;
}

bool Board::verifyWinner(const Player& player)
{
	std::queue<Pylon*> nextVisit;
	std::unordered_set<Pylon*> visited;

	for (int i = 0; i < m_board.size(); ++i)
	{
		Pylon* currPylon;
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
		Pylon* currPylon;
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


