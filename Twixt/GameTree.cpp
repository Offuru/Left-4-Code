#include "GameTree.h"

twixt::GameTree::GameTree(size_t depth, Pylon::Color color) :
	GameTree{ Board{}, depth, color }
{}

twixt::GameTree::GameTree(Board rootGame, size_t depth, Pylon::Color color) :
	m_depth{ depth }, m_root{ std::move(rootGame), nullptr, NodeVec{} , 0, 0, 0 }
{}

twixt::NodeRef twixt::GameTree::selection(NodeRef curr_node)
{
	double maxUCB = -std::numeric_limits<float>::infinity();
	Node selected_child;

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

twixt::NodeVec twixt::GameTree::generateAllStates(NodeRef curr_node)
{
	NodeVec children;

	if (m_color == Pylon::Color::Black)
	{
		std::reference_wrapper<std::vector<std::vector<twixt::Foundation>>> currentBoard = curr_node.get().currentBoard.getBoard();

		//choose the the leftmost pylon
		nonstd::observer_ptr<Pylon> leftmost{ nullptr };

		for (int i = 0; i < currentBoard.get().size() && leftmost == nullptr; ++i)
		{
			for (int j = 0; j < currentBoard.get().size() && leftmost == nullptr; ++j)
			{
				if (currentBoard.get()[j][i].getPylon() != nullptr)
				{
					if (currentBoard.get()[j][i].getPylon()->getColor() == m_color)
						leftmost = currentBoard.get()[j][i].getPylon();
				}
			}
		}

		//choose the rightmost pylon
		nonstd::observer_ptr<Pylon> rightmost{ nullptr };

		for (int i = currentBoard.get().size() - 1 ; i >= 0 && rightmost == nullptr; --i)
		{
			for (int j = 0; j < currentBoard.get().size() && rightmost == nullptr; ++j)
			{

			}
		}
	}
}




