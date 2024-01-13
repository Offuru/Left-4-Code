#pragma once
#include <memory>
#include <vector>
#include <numbers>
#include <optional>
#include "observer_ptr.h"
#include "Pylon.h"

struct BoardState
{
	size_t boardSize;
	std::unordered_map<std::pair<uint8_t, uint8_t>, uint8_t> pylons; //1 - red, 2 - black
	bool currentPlayer; //0 - red, 1 - black
};

struct Node
{
	using NodePtr = std::unique_ptr<Node>;
	using NodeRef = std::reference_wrapper<Node>;
	using NodeObsPtr = nonstd::observer_ptr<Node>;
	using PosPair = std::pair<twixt::Position, twixt::Position>;

	twixt::Position pylon;
	std::vector<std::optional<PosPair>> bridges;

	BoardState state;
	NodeObsPtr parent;
	std::vector<NodePtr> children;

	float score;
	int visits;
	int height;

	__declspec(dllexport) double UCB() const;

	__declspec(dllexport) bool isLeaf() const;

	__declspec(dllexport) Node(BoardState state, NodeObsPtr parent, const twixt::Position& pylon, int height);
};