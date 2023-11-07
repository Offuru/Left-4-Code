#include <iostream>
#include "Game.h"
int main()
{
	Game test;

	test.addPylon(std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	test.addPylon(std::make_pair(3, 6), Pylon::Type::Cross, Pylon::Color::Red);
	test.printBoard();
	return 0;
}