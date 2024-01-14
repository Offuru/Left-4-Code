#include "MonteCarloTree.h"

twixt::MonteCarloTree::MonteCarloTree(Game& game, Pylon::Color color, uint8_t maxHeight, uint8_t maxRollbackHeight, uint8_t maxActions) :
	m_maxHeight{ maxHeight }, m_maxRollbackHeight{ maxRollbackHeight }, m_maxActions{ maxActions }
{
	m_maxUCBLambda = [](const NodePtr& a, const NodePtr& b) { return(a->UCB() > b->UCB()); };
	m_aggressiveness = 0.2;
	m_expansion = 1.;

	if (game.getRound() == 5)
	{
		std::cout << 5 << '\n';
		m_aggressiveness = 0.05;
		m_expansion = 5.;
	}

	///create root state from given board


	///selection

	///set root as current state
	///while current state isnt a leaf select a child as current based on its UCB value


	///expansion

	///if the current node hasnt been visited immediately start rollback
	///else add a new state to the children for each available action, then rollback


	///simulation

	///during rollback, if a terminal node (has height maxRollbackHeight) has been reached, take its value and back propagate


	///backpropagation

	///once the tree has reached satisfactory (maxHeight) height, return the root child with the highest score

	BoardState startState;
	startState.boardSize = game.getBoard().getSize();
	startState.currentPlayer = (color == Pylon::Color::Red ? 0 : 1);
	for (size_t i = 0; i < game.getBoard().getSize(); ++i)
		for (size_t j = 0; j < game.getBoard().getSize(); ++j)
		{
			nonstd::observer_ptr<Pylon> pylon = game.getBoard().getBoard()[i][j].getPylon();
			if (pylon != nullptr)
				startState.pylons.emplace(std::make_pair(i, j), (pylon->getColor() == Pylon::Color::Red ? 1 : 2));
		}

	m_root = std::make_unique<Node>(startState, nullptr, std::make_pair(0, 0), 0);

	NodeObsPtr rootObs = nonstd::make_observer(m_root.get());
	expansion(rootObs);

	while (true)
	{
		NodeObsPtr leaf = selection(rootObs);
		if (leaf->height > maxHeight)
			break;

		if (leaf->visits != 0 && leaf->children.size() == 0)
		{
			expansion(leaf);
			leaf = nonstd::make_observer(leaf->children[0].get());
		}

		backPropagation(leaf, rollback(leaf));
	}
}

twixt::Position twixt::MonteCarloTree::getBestMove() const
{
	return (std::ranges::max_element(m_root->children,
		[](const auto& nodeA, const auto& nodeB) { return nodeA->score > nodeB->score; }))->get()->pylon;
}

Node::NodeObsPtr twixt::MonteCarloTree::selection(NodeObsPtr node)
{
	if (node->isLeaf())
		return node;
	if (node->state.currentPlayer)
		return selection(nonstd::make_observer(std::ranges::min_element(node->children, m_maxUCBLambda)->get()));
	else
		return selection(nonstd::make_observer(std::ranges::max_element(node->children, m_maxUCBLambda)->get()));
}

void twixt::MonteCarloTree::expansion(NodeObsPtr node)
{
	std::vector<Position> actions = getPossibleActions(node);

	for (const auto& action : actions)
	{
		BoardState newState = node->state;
		uint8_t boardSize = (uint8_t)sqrt(node->state.boardSize);
		newState.pylons.insert({ action, node->state.currentPlayer });
		newState.currentPlayer = !node->state.currentPlayer;

		node->children.emplace_back(std::make_unique<Node>(newState, node, action, node->height + 1));
	}
}

double twixt::MonteCarloTree::rollback(NodeObsPtr node)
{
	size_t depth = 0;
	NodePtr simulation = std::make_unique<Node>(node->state, node, std::make_pair(0, 0), 0);
	uint8_t boardSize = (uint8_t)sqrt(node->state.boardSize);
	std::random_device rd;
	std::mt19937 gen(rd());

	while (depth != m_maxRollbackHeight)
	{
		depth++;
		std::vector<Position> actions = getPossibleActions(nonstd::make_observer(simulation.get()));

		std::uniform_int_distribution<> distrib(0, std::max((int)actions.size() - 1, (int)0));
		Position action = actions[distrib(gen)];

		simulation->state.currentPlayer = !simulation->state.currentPlayer;
		simulation->state.pylons.insert({ action, simulation->state.currentPlayer ? 2 : 1 });
	}

	return getScore(simulation->state);
}

void twixt::MonteCarloTree::backPropagation(NodeObsPtr node, double val)
{
	while (node != nullptr)
	{
		node->score += val;
		node->visits++;
		node = node->parent;
	}
}

double twixt::MonteCarloTree::getScore(BoardState state)
{
	double redArea = 0, blackArea = 0;

	int8_t di[] = { -2,-1,1,2,2,1,-1,-2 };
	int8_t dj[] = { 1,2,2,1,-1,-2,-2,-1 };

	std::vector<std::vector<uint8_t>> matrix;
	matrix.resize(state.boardSize, std::vector<uint8_t>(state.boardSize));

	std::queue<Position> frontiers;

	for (const auto& pylon : state.pylons)
	{
		const auto& [i, j] = pylon.first;
		matrix[i][j] = pylon.second;
		frontiers.push(pylon.first);
		if (pylon.second == 1)
			redArea++;
		else
			blackArea++;
	}

	for (size_t i = 1; i < state.boardSize - 1; ++i)
	{
		frontiers.emplace(1, i);
		frontiers.emplace(i, 1);
		frontiers.emplace(i, state.boardSize - 1);
		frontiers.emplace(state.boardSize - 1, i);

		matrix[1][i] = 1;
		matrix[1][state.boardSize - 1] = 1;
		matrix[i][1] = 2;
		matrix[i][state.boardSize - 1] = 2;
	}

	redArea += 2 * (state.boardSize - 2);
	blackArea += 2 * (state.boardSize - 2);

	while (!frontiers.empty())
	{
		const auto& [i, j] = frontiers.front();
		frontiers.pop();

		for (int8_t k = 0; k < 8; ++k)
		{
			int8_t newI = i + di[k];
			int8_t newJ = j + dj[k];

			if (validPosition(newI, newJ, state.boardSize, state.currentPlayer) && matrix[newI][newJ] == 0)
			{
				matrix[newI][newJ] = matrix[i][j];
				matrix[i][j] == 1 ? redArea++ : blackArea++;
				frontiers.emplace(newI, newJ);
			}
		}
	}

	double connectedRed = 0, connectedBlack = 0;

	for (const auto& pylon : state.pylons)
		if (pylon.second == 1)
			for (int k = 2; k < 6; ++k)
			{
				int8_t i = pylon.first.first, j = pylon.first.second;
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize, state.currentPlayer) && matrix[newI][newJ] == pylon.second)
				{
					if (checkAround(matrix, { newI,newJ }))
						continue;
					uint8_t distance = std::min((size_t)newI, matrix.size() - newI);
					connectedRed += (matrix.size() - distance);
				}
			}
		else
			for (int k = 0; k < 4; ++k)
			{
				int8_t i = pylon.first.first, j = pylon.first.second;
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize, state.currentPlayer) && matrix[newI][newJ] == pylon.second)
				{
					if (checkAround(matrix, { newI,newJ }))
						continue;
					uint8_t distance = std::min((size_t)newJ, matrix.size() - newJ);
					connectedBlack += (matrix.size() - distance);
				}
			}

	return (m_aggressiveness * (redArea - blackArea) + m_expansion * (connectedRed - connectedBlack));
}

bool twixt::MonteCarloTree::checkAround(const std::vector<std::vector<uint8_t>>& matrix, const Position& pos)
{
	int8_t di[] = { -1,-1,-1,0,1,1,1,0 };
	int8_t dj[] = { -1,0,1,1,1,0,-1,-1 };

	for (uint8_t k = 0; k < 8; ++k)
	{
		int8_t newI = pos.first + di[k], newJ = pos.second;
		if (matrix[pos.first][pos.second] == matrix[newI][newJ])
			return true;
	}

	return false;
}

std::vector<twixt::Position> twixt::MonteCarloTree::getPossibleActions(NodeObsPtr node)
{
	std::vector<std::pair<twixt::Position, double>> actions;

	std::vector<std::vector<uint8_t>> matrix;
	matrix.resize(node->state.boardSize, std::vector<uint8_t>(node->state.boardSize));
	for (const auto& pylon : node->state.pylons)
		matrix[pylon.first.first][pylon.first.second] = pylon.second;
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		matrix[0][i] = 1;
		matrix[matrix.size() - 1][i] = 1;
		matrix[i][0] = 2;
		matrix[i][matrix.size() - 1] = 2;
	}

	std::array <Position, 4> corners = { std::make_pair(0,0),{0,matrix.size() - 1},
										 {matrix.size() - 1,0},{matrix.size() - 1,matrix.size() - 1}
									   };

	//phase 1: check for influence zones in a 10x10 square in the middle
	BoardState newState = node->state;
	for (size_t i = 7; i < matrix.size() - 7; ++i)
		for (size_t j = 7; j < matrix.size() - 7; ++j)
			if (std::ranges::find(corners, std::make_pair(i, j)) == corners.end() && matrix[i][j] == 0)
			{
				if (((i == 0 || i == matrix.size() - 1) && !newState.currentPlayer) ||
					((j == 0 || j == matrix.size() - 1) && newState.currentPlayer) || checkAround(matrix, { i,j }))
					continue;
				newState.pylons.emplace(std::make_pair(i, j), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(i, j), getScore(newState));
				newState.pylons.erase({ i,j });
			}

	//phase 2: check for bridge extensions for existing pylons

	int8_t blackDI[] = { -1,1,1,-1 };
	int8_t blackDJ[] = { 2,2,-2,-2 };
	int8_t redDI[] = { -2, 2, 2, -2 };
	int8_t redDJ[] = { 1,1,-1,-1 };

	for (const auto& pylon : newState.pylons)
	{
		int8_t i = pylon.first.first, j = pylon.first.second;
		for (uint8_t k = 0; k < 4; ++k)
		{
			int8_t newI = i + blackDI[k], newJ = j + blackDJ[k];
			if (pylon.second == 1)
				newI = i + redDI[k], newJ = j + redDJ[k];

			if (validPosition(newI, newJ, matrix.size(), pylon.second) && matrix[newI][newJ] == 0)
			{
				newState.pylons.emplace(std::make_pair(newI, newJ), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(newI, newJ), getScore(newState));
				newState.pylons.erase({ newI,newJ });
			}
		}
	}

	if (m_root->state.currentPlayer)
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second < b.second; });
	else
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second > b.second; });

	std::vector<Position> answer;
	uint8_t n = std::min((uint8_t)actions.size(), m_maxActions);
	for (uint8_t i = 0; i < n; ++i)
		answer.emplace_back(actions[i].first);

	return answer;
}

bool twixt::MonteCarloTree::validPosition(int8_t posX, int8_t posY, uint8_t boardSize, bool black) const
{
	if (!(posX >= 0 && posX < boardSize && posY >= 0 && posY < boardSize))
		return false;

	if (!black && (posY == 0 || posY == boardSize - 1))
		return false;

	if (black && (posX == 0 || posX == boardSize - 1))
		return false;

}
