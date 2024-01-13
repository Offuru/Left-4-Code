#include "Node.h"

double Node::UCB() const
{
	if (visits == 0)
		return std::numeric_limits<double>::infinity();
	return score / visits + 2 * sqrt((log(parent->visits) / visits));
}

bool Node::isLeaf() const
{
	return children.size() == 0;
}

Node::Node(BoardState state, NodeObsPtr parent, const twixt::Position& pylon, int height) :
	state{ state }, parent{ parent }, pylon{ pylon }, bridges{ bridges }, height{ height }
{
	visits = 0;
	score = 0;
}


