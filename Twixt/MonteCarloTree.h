#pragma once
#include <unordered_map>
#include <array>
#include <ranges>
#include <queue>
#include "Node.h"
#include "Game.h"
#include <iostream>

namespace twixt
{
	using NodePtr = Node::NodePtr;
	using NodeObsPtr = Node::NodeObsPtr;
	using NodeRef = Node::NodeRef;

	class MonteCarloTree
	{
	public:
		//player == false = black
		MonteCarloTree(Game& game, Pylon::Color color, uint8_t maxHeight = 4, uint8_t maxRollbackHeight = 4, uint8_t maxActions = 5);
		Position getBestMove() const;

	private:
		NodeObsPtr selection(NodeObsPtr node);
		void expansion(NodeObsPtr node);
		double rollback(NodeObsPtr node);
		void backPropagation(NodeObsPtr node, double val);

		double getScore(BoardState state);
		bool checkAround(const std::vector<std::vector<uint8_t>>& matrix, const Position& pos);

		std::vector<Position> getPossibleActions(NodeObsPtr);

		bool validPosition(int8_t posX, int8_t posY, uint8_t boardSize, bool black) const;

		Node::NodePtr m_root;
		uint8_t m_maxHeight;
		uint8_t m_maxRollbackHeight;
		uint8_t m_maxActions;
		double m_aggressiveness;
		double m_expansion;

		std::function<bool(const NodePtr&, const NodePtr&)> m_maxUCBLambda;

	};
}

