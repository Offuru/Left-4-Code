#pragma once
#include <unordered_map>
#include <array>
#include <ranges>
#include <queue>
#include "Node.h"
#include "Board.h"
#include <iostream>

namespace twixt
{
	using NodePtr = Node::NodePtr;
	using NodeObsPtr = Node::NodeObsPtr;
	using NodeRef = Node::NodeRef;

	class MonteCarloTree
	{
	public:

		MonteCarloTree(Board& board, bool player = false, uint8_t maxHeight = 3, uint8_t maxRollbackHeight = 2, uint8_t maxActions = 2);
		Position getBestMove() const;

	private:
		NodeObsPtr selection(NodeObsPtr node);
		void expansion(NodeObsPtr node);
		double rollback(NodeObsPtr node);
		void backPropagation(NodeObsPtr node, double val);

		double getScore(BoardState state);

		std::vector<Position> getPossibleActions(NodeObsPtr);

		bool validPosition(int8_t i, int8_t j, uint8_t boardSize) const;

		Node::NodePtr m_root;
		uint8_t m_maxHeight;
		uint8_t m_maxRollbackHeight;
		uint8_t m_maxActions;

		std::function<bool(const NodePtr&, const NodePtr&)> m_maxUCBLambda;

	};
}

