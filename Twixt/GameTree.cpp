#include "GameTree.h"

twixt::GameTree::GameTree(size_t depth) :
	GameTree{ Board{}, depth }
{}

twixt::GameTree::GameTree(Board rootGame, size_t depth) :
	m_depth{ depth }, m_root{ std::move(rootGame), nullptr }
{}

twixt::NodeRef twixt::GameTree::selection(NodeRef curr_node)
{
	double maxUCB = -std::numeric_limits<float>::infinity();
	Node selected_child = curr_node.get();

	for (auto child : curr_node.get().children)
	{
		float currUCB = child.UCB();
		if (currUCB > maxUCB)
		{
			maxUCB = currUCB;
			selected_child = child;
		}
	}

	return std::reference_wrapper<Node>(selected_child);
}

twixt::NodeRef twixt::GameTree::expansion(NodeRef curr_node, bool black)
{
	if (curr_node.get().isLeaf())
		return curr_node;

	Node selected_node = curr_node.get();

	if (black)
	{
		double maxUCB = -std::numeric_limits<float>::infinity();
		for (auto child : selected_node.children)
		{
			double currUCB = child.UCB();
			if (currUCB > maxUCB)
			{
				maxUCB = currUCB;
				selected_node = child;
			}
		}
	}
	else
	{
		double minUCB = std::numeric_limits<float>::infinity();
		for (auto child : selected_node.children)
		{
			double currUCB = child.UCB();
			if (currUCB < minUCB)
			{
				minUCB = currUCB;
				selected_node = child;
			}
		}
	}

	return expansion(std::reference_wrapper<Node>(selected_node), !black);
}

twixt::NodeVec twixt::GameTree::generatePossibleStates(NodeRef curr_node, bool black)
{
	NodeVec children;


	std::reference_wrapper<std::vector<std::vector<twixt::Foundation>>> currentBoard = curr_node.get().currentBoard.getBoard();

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, currentBoard.get().size() - 1);

	nonstd::observer_ptr<Pylon> leftmost{ nullptr };
	nonstd::observer_ptr<Pylon> rightmost{ nullptr };

	Pylon::Color currentColor = (black) ? Pylon::Color::Black : Pylon::Color::Red;

	if (black)
	{
		//choose the the leftmost pylon
		for (int i = 0; i < currentBoard.get().size() && leftmost == nullptr; ++i)
		{
			for (int j = 0; j < currentBoard.get().size() && leftmost == nullptr; ++j)
			{
				if (currentBoard.get()[j][i].getPylon() != nullptr)
				{
					if (currentBoard.get()[j][i].getPylon()->getColor() == Pylon::Color::Black)
						leftmost = currentBoard.get()[j][i].getPylon();
				}
			}
		}


		//choose the rightmost pylon
		for (int i = currentBoard.get().size() - 1; i >= 0 && rightmost == nullptr; --i)
		{
			for (int j = 0; j < currentBoard.get().size() && rightmost == nullptr; ++j)
			{
				if (currentBoard.get()[j][i].getPylon() != nullptr)
				{
					if (currentBoard.get()[j][i].getPylon()->getColor() == Pylon::Color::Black)
						rightmost = currentBoard.get()[j][i].getPylon();
				}
			}
		}

	}
	else
	{
		//for red
	}


	bool addedState = false;
	
	//if no pylons were found, then pick a random position on board
	if (leftmost == nullptr && rightmost == nullptr)
	{
		//make a copy of current board where adding the new pylon
		Board newBoard(curr_node.get().currentBoard);

		size_t posX = distrib(gen), posY = distrib(gen);
		Foundation& foundation = newBoard[{ posX, posY }];

		while (foundation.getBob()
			|| foundation.getExploded()
			|| foundation.getPylon() == nullptr)
		{
			posX = distrib(gen), posY = distrib(gen);
			foundation = newBoard[{ posX, posY }];
		}

		newBoard.addPylon(newBoard[{ posX, posY }],
			Pylon::Color::Black, Pylon::Type::Single);


		children.emplace_back(std::move(newBoard), &(curr_node.get()),
			std::make_optional<twixt::Position>({ posX, posY }));

		addedState = true;
	}
	//if only 1 pylon exists, choose one of the 8 adjacent pos
	else if (leftmost == rightmost)
	{
		int dx[10] = { 1, 2, -1, -2, 1, -1, 2, -2 };
		int dy[10] = { 2, 1, -2, -1, -2, 2, -1, -1 };

		auto& [currX, currY] = curr_node.get().position.value();

		for (int i = 0; i < 8; ++i)
		{
			Foundation& foundation = curr_node.get().currentBoard[{ dx[i] + currX, dy[i] + currY }];
			if (foundation.getBob()
				|| foundation.getExploded()
				|| foundation.getPylon() != nullptr
				|| !inBounds(dx[i] + currX, dy[i] + currY, currentBoard.get().size()))
				continue;

			Board newBoard(curr_node.get().currentBoard);

			newBoard.addPylon(newBoard[{ dx[i], dy[i] }],
				Pylon::Color::Black, Pylon::Type::Single);

			children.emplace_back(std::move(newBoard), &(curr_node.get()),
				std::make_optional<twixt::Position>({ dx[i], dy[i] }),
				std::make_optional<std::pair<twixt::Position, twixt::Position>>({ {dx[i], dy[i]}, curr_node.get().position.value() }));

			addedState = true;
		}
	}
	else
	{
		int dx[10] = { 1, 2, -1, -2, 1, -1, 2, -2 };
		int dy[10] = { 2, 1, -2, -1, -2, 2, -1, -1 };

		//idk yet
	}





	return children;
}

bool twixt::GameTree::inBounds(size_t posX, size_t posY, size_t boardSize)
{
	return posX >= 0 && posX < boardSize && posY >= 0 && posY < boardSize;
}




