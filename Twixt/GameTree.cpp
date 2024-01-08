#include "GameTree.h"

twixt::GameTree::GameTree(size_t depth) :
	GameTree{ Board{}, depth }
{}

twixt::GameTree::GameTree(Board rootGame, size_t depth) :
	m_depth{ depth }, m_root{ std::move(rootGame), nullptr, NodeVec{} , 0, 0, 0}
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

twixt::NodeRef twixt::GameTree::expansion(NodeRef curr_node)
{
	if (curr_node.get().isLeaf())
		return curr_node;

	Node selected_node = curr_node.get();

	while (!selected_node.isLeaf())
	{
		double maxUCB = -std::numeric_limits<float>::infinity();
		
		for (auto child : selected_node.children)
		{
			float currUCB = child.UCB();
			if (currUCB > maxUCB)
			{
				maxUCB = currUCB;
				selected_node = child;
			}
		}
	}

	return std::reference_wrapper<Node>(selected_node);
}




