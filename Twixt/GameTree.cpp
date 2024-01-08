#include "GameTree.h"

twixt::GameTree::GameTree(size_t depth) :
	GameTree{ Board{}, depth }
{}

twixt::GameTree::GameTree(Board rootGame, size_t depth) :
	m_depth{ depth }, m_root{ std::move(rootGame), nullptr, NodeVec{} }
{}


