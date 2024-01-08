#pragma once
#include "Board.h"


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

		float UCB{}; //upper confidence bound

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

	private:
		size_t m_depth;
		Node m_root;
	};
}
