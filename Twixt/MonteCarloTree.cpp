#include "MonteCarloTree.h"

twixt::MonteCarloTree::MonteCarloTree(Board& board, Pylon::Color color, uint8_t maxHeight, uint8_t maxRollbackHeight, uint8_t maxActions) :
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
	startState.currentPlayer = (color == Pylon::Color::Red) ? 0 : 1;


	for (size_t i = 0; i < board.getSize(); ++i)
		for (size_t j = 0; j < board.getSize(); ++j)
			if (board.getBoard()[i][j].getPylon() != nullptr)
			{
				startState.pylons.emplace(std::make_pair(i, j), (board.getBoard()[i][j].getPylon()->getColor() == Pylon::Color::Red) ? 1 : 2);
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

	if (m_root->state.currentPlayer == 0)
		return (std::ranges::max_element(m_root->children,
			[](const auto& nodeA, const auto& nodeB) { return nodeA->score > nodeB->score; }))->get()->pylon;
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
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize, state.currentPlayer) && matrix[newI][newJ] == pylon.second)
					++connectedRed;
			}
		else
			for (int k = 0; k < 4; ++k)
			{
				int8_t newI = pylon.first.first + di[k], newJ = pylon.first.second + dj[k];
				if (validPosition(newI, newJ, state.boardSize, state.currentPlayer) && matrix[newI][newJ] == pylon.second)
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

	std::queue<twixt::Position> frontier;

	for (size_t i = 0; i < matrix.size(); ++i)
		for (size_t j = 0; j < matrix.size(); ++j)
			if ((matrix[i][j] == 1 && !node->state.currentPlayer) || (matrix[i][j] == 2 && node->state.currentPlayer))
			{
				frontier.push({ i, j });
			}


	std::array<int, 8> rightOrUpDX = { 1,2,2,1, -2, -1, 1, 2 };
	std::array<int, 8> rightOrUpDY = { 2,1,-1,-2, 1, 2, 2, 1 };

	std::array<int, 8> leftOrDownDX = { -1, -2, -2, -1, -2, -1, 1, 2 };
	std::array<int, 8> leftOrDownDY = { 2, 1, -1, -2, -1, -2, -2, -1 };
	BoardState newState = node->state;

	int start = (!newState.currentPlayer) ? 0 : 4;
	int end = (!newState.currentPlayer) ? 4 : 8;

	std::vector<std::vector<uint8_t>> matrixTmp = matrix;
	twixt::Position rightMost{ 0, 0 }, leftMost{ newState.boardSize - 1 , newState.boardSize - 1 };
	while (!frontier.empty())
	{
		auto& [x, y] = frontier.front();
		frontier.pop();
		matrixTmp[x][y] = 0; //visited
		if (!newState.currentPlayer)
		{
			if (leftMost.first > x)
			{
				leftMost = { x, y };
			}
			if (rightMost.first < x)
			{
				rightMost = { x , y };
			}
		}
		else
		{
			if (leftMost.second > y)
			{
				leftMost = { x , y };
			}
			if (rightMost.second < y)
			{
				rightMost = { x , y };
			}
		}


		//get leftmost or down
		for (int i = start; i < end; ++i)
		{
			if (newState.currentPlayer) //black
			{
				if (validPosition(x + leftOrDownDX[i], y + leftOrDownDY[i], newState.boardSize, newState.currentPlayer) &&
					matrixTmp[x + leftOrDownDX[i]][y + leftOrDownDY[i]] == 2)
				{
					frontier.push({ x + leftOrDownDX[i] , y + leftOrDownDY[i] });

				}
			}
			else
			{
				if (validPosition(x + leftOrDownDX[i], y + leftOrDownDY[i], newState.boardSize, newState.currentPlayer) &&
					matrixTmp[x + leftOrDownDX[i]][y + leftOrDownDY[i]] == 1)
				{
					frontier.push({ x + leftOrDownDX[i] , y + leftOrDownDY[i] });

				}
			}
		}

		//get rightmost or up
		for (int i = start; i < end; ++i)
		{
			if (newState.currentPlayer) //black
			{
				if (validPosition(x + rightOrUpDX[i], y + rightOrUpDY[i], newState.boardSize, newState.currentPlayer)
					&& matrixTmp[x + rightOrUpDX[i]][y + rightOrUpDY[i]] == 2)
				{
					frontier.push({ x + rightOrUpDX[i] , y + rightOrUpDY[i] });

				}
			}
			else
			{
				if (validPosition(x + rightOrUpDX[i], y + rightOrUpDY[i], newState.boardSize, newState.currentPlayer)
					&& matrixTmp[x + rightOrUpDX[i]][y + rightOrUpDY[i]] == 1)
				{
					frontier.push({ x + rightOrUpDX[i] , y + rightOrUpDY[i] });

				}
			}
		}
	}

	bool addedPylon = false;

	std::array<int, 8> dx = { 1, 2, -1, -2, 1, -1, 2, -2 };
	std::array<int, 8> dy = { 2, 1, -2, -1, -2, 2, -1, -1 };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, newState.boardSize - 1);


	if (leftMost == rightMost)
	{
		auto& [currX, currY] = leftMost;
		for (int i = 0; i < 8; ++i)
		{
			if (validPosition(currX + dx[i], currY + dy[i], newState.boardSize, newState.currentPlayer)
				&& matrix[currX + dx[i]][currY + dy[i]] == 0)
			{
				newState.pylons.emplace(std::make_pair(currX + dx[i], currY + dy[i]), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(currX + dx[i], currY + dy[i]), getScore(newState));
				newState.pylons.erase(std::make_pair(currX + dx[i], currY + dy[i]));
				addedPylon = true;
			}
		}
	}
	else if (leftMost != rightMost && leftMost != std::make_pair(newState.boardSize - 1, 0) && rightMost != std::make_pair(0, newState.boardSize - 1))
	{
		auto& [currX, currY] = rightMost;
		for (int i = start; i < end; ++i)
		{
			if (validPosition(currX + rightOrUpDX[i], currY + rightOrUpDY[i], newState.boardSize, newState.currentPlayer)
				&& matrix[currX + rightOrUpDX[i]][currY + rightOrUpDY[i]] == 0)
			{
				newState.pylons.emplace(std::make_pair(currX + rightOrUpDX[i], currY + rightOrUpDY[i]), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(currX + rightOrUpDX[i], currY + rightOrUpDY[i]), getScore(newState));
				newState.pylons.erase(std::make_pair(currX + rightOrUpDX[i], currY + rightOrUpDY[i]));
				addedPylon = true;
			}
		}

		auto& [currX2, currY2] = leftMost;
		for (int i = start; i < end; ++i)
		{
			if (validPosition(currX2 + leftOrDownDX[i], currY2 + leftOrDownDY[i], newState.boardSize, newState.currentPlayer)
				&& matrix[currX2 + leftOrDownDX[i]][currY2 + leftOrDownDY[i]] == 0)
			{
				newState.pylons.emplace(std::make_pair(currX2 + leftOrDownDX[i], currY2 + leftOrDownDY[i]), newState.currentPlayer ? 2 : 1);
				actions.emplace_back(std::make_pair(currX2 + leftOrDownDX[i], currY2 + leftOrDownDY[i]), getScore(newState));
				newState.pylons.erase(std::make_pair(currX2 + leftOrDownDX[i], currY2 + leftOrDownDY[i]));
				addedPylon = true;
			}
		}
	}
	if (!addedPylon)
	{
		twixt::Position tmpPos = { distrib(gen), distrib(gen) };

		newState.pylons.emplace(std::make_pair(tmpPos.first, tmpPos.second), newState.currentPlayer ? 2 : 1);
		actions.emplace_back(std::make_pair(tmpPos.first, tmpPos.second), getScore(newState));
		newState.pylons.erase(tmpPos);
	}


	std::vector<Position> answer;
	if (m_root->state.currentPlayer)
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second < b.second; });
	else
		std::ranges::sort(actions, [](const auto& a, const auto& b) {return a.second > b.second; });

	for (size_t i = 0; i < std::min((uint8_t)actions.size(), m_maxActions); ++i)
		answer.emplace_back(actions[i].first);
	std::cout << answer.size() << "\n\n";
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

	return true;
}
