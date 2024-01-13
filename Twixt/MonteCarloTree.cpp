#include "MonteCarloTree.h"

twixt::MonteCarloTree::MonteCarloTree(Board& board, bool player, uint8_t maxHeight, uint8_t maxRollbackHeight, uint8_t maxActions) :
	m_maxHeight{ maxHeight }, m_maxRollbackHeight{ maxRollbackHeight }, m_maxActions{ maxActions }
{
	m_maxUCBLambda = [](const NodePtr& a, const NodePtr& b) { return(a->UCB() > b->UCB()); };

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
	startState.boardSize = board.getSize();
	startState.currentPlayer = player;
	for (size_t i = 0; i < board.getSize(); ++i)
		for (size_t j = 0; j < board.getSize(); ++j)
			if (board.getBoard()[i][j].getPylon() != nullptr)
				startState.pylons.emplace(std::make_pair(i, j), player ? 2 : 1);

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
	size_t redArea = 0, blackArea = 0;

	int8_t di[] = { -2,-1,1,2,2,1,-1,-2 };
	int8_t dj[] = { 1,2,2,1,-1,-2,-2,-1 };

	std::vector<std::vector<uint8_t>> matrix;
	matrix.resize(state.boardSize, std::vector<uint8_t>(state.boardSize));

	std::queue<Position> frontiers;

	for (const auto& pylon : state.pylons)
	{
		const auto& [i, j] = pylon.first;
		matrix[i][j] = pylon.second;
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

			if (validPosition(newI, newJ, state.boardSize) && matrix[newI][newJ] == 0)
			{
				matrix[newI][newJ] = matrix[i][j];
				matrix[i][j] == 1 ? redArea++ : blackArea++;
				frontiers.emplace(newI, newJ);
			}
		}
	}

	uint8_t connectedRed = 0, connectedBlack = 0;

	for (const auto& pylon : state.pylons)
		if (pylon.second == 1)
			for (int k = 2; k < 6; ++k)
			{
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize) && matrix[newI][newJ] == pylon.second)
					++connectedRed;
			}
		else
			for (int k = 0; k < 4; ++k)
			{
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize) && matrix[newI][newJ] == pylon.second)
					++connectedBlack;
			}

	return (redArea - blackArea + connectedRed - connectedBlack);
}

std::vector<twixt::Position> twixt::MonteCarloTree::getPossibleActions(NodeObsPtr node)
{
	std::vector<std::pair<twixt::Position, double>> actions;

	std::vector<std::vector<uint8_t>> matrix;
	matrix.resize(node->state.boardSize, std::vector<uint8_t>(node->state.boardSize));
	for (const auto& pylon : node->state.pylons)
		matrix[pylon.first.first][pylon.first.second] = pylon.second;

	std::array <Position, 4> corners = { std::make_pair(0,0),{0,matrix.size() - 1},
										 {matrix.size() - 1,0},{matrix.size() - 1,matrix.size() - 1}
	};

	BoardState newState = node->state;
	for (size_t i = 0; i < matrix.size(); ++i)
		for (size_t j = 0; j < matrix.size(); ++j)
			if (std::ranges::find(corners, std::make_pair(i, j)) == corners.end() && matrix[i][j] == 0)
			{
				if (((i == 0 || i == matrix.size() - 1) && !newState.currentPlayer) ||
					((j == 0 || j == matrix.size() - 1) && newState.currentPlayer))
					continue;
				newState.pylons.emplace(std::make_pair(i, j), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(i, j), getScore(newState));
				newState.pylons.erase({ i,j });
			}

	if (m_root->state.currentPlayer)
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second < b.second; });
	else
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second > b.second; });

	std::vector<Position> answer;

	for (size_t i = 0; i < std::min((uint8_t)actions.size(), m_maxActions); ++i)
		answer.emplace_back(actions[i].first);

	return answer;
}

bool twixt::MonteCarloTree::validPosition(int8_t i, int8_t j, uint8_t boardSize) const
{
	return 0 <= i && i < boardSize && 0 <= j && j < boardSize;
}
