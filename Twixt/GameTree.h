#pragma once
#include "Board.h"
#include <limits>
#include <numbers>

namespace twixt
{
	struct Node;

	using NodePtr = Node*;
	using NodeRef = std::reference_wrapper<Node>;
	using NodeVec = std::vector<Node>;
	using NodeRefVec = std::vector<NodeRef>;

	struct Node
	{
		Board currentBoard;
		NodePtr parent;
		NodeVec children;

		float winningScore{};
		int parentVisits{};
		int currentVisists{};

		//upper confidence bound
		double UCB() const
		{
			double ans = winningScore + 2 * sqrt((log(parentVisits + std::numbers::e * pow(10.0, -6.0)) / (currentVisists + pow(10., -10.))));
			return ans;
		}

		bool isLeaf() const noexcept
		{
			return children.size() == 0;
		}
	};


	class GameTree
	{
	public:

		GameTree(size_t depth = 0u);

		GameTree(Board rootGame, size_t depth = 0u);

		NodeRef selection(NodeRef curr_node);
		NodeRef expansion(NodeRef curr_node);

	private:
		size_t m_depth;
		Node m_root;
	};
}
