#include <iostream>
#include "Game.h"
int main()
{
	Game test;

	test.addPylon(std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	test.addPylon(std::make_pair(4, 5), Pylon::Type::Single, Pylon::Color::Red);
	test.addPylon(std::make_pair(5, 5), Pylon::Type::Single, Pylon::Color::Red);
	test.addPylon(std::make_pair(4, 6), Pylon::Type::Single, Pylon::Color::Red);
	test.addBridge(std::make_pair(3, 3), std::make_pair(4, 5));
	test.addBridge(std::make_pair(3, 4), std::make_pair(4, 6));
	test.addBridge(std::make_pair(4, 3), std::make_pair(5, 5));
	test.printBoard();
	return 0;
}