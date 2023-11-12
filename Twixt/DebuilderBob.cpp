#include "DebuilderBob.h"

DebuilderBob::DebuilderBob(uint8_t boardSize)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, boardSize - 1);
	m_position = { distrib(gen),  distrib(gen) };
}
