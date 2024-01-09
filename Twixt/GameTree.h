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

		std::optional<twixt::Position> position;
		std::optional<std::pair<twixt::Position, twixt::Position>> bridge; //bridge ends positions

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

		Node(Board board, NodePtr parent,
			std::optional<twixt::Position> position = std::nullopt,
			std::optional<std::pair<twixt::Position, twixt::Position>> bridge = std::nullopt) :
			currentBoard{ board }, parent{ parent }, children{ children },
			position{ position }, bridge{ bridge }
		{
			children = NodeVec{};
			winningScore = 0;
			parentVisits = currentVisists = 0;
		}

	};


	class GameTree
	{
	public:

		GameTree(size_t depth = 0u);

		GameTree(Board rootGame, size_t depth = 0u);

		NodeRef selection(NodeRef curr_node);
		NodeRef expansion(NodeRef curr_node, bool black);


		NodeVec generatePossibleStates(NodeRef curr_node, bool black);

	private:
		size_t m_depth;
		Node m_root;
		Pylon::Color m_color; //helps with generateAllStates so we don't generate ALL possible states because
		//there would be too many of them

		bool inBounds(size_t posX, size_t posY, size_t boardSize);
	};
}
