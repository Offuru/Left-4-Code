#include <iostream>
#include "Game.h"
int main()
{
	Game test;
	test.setReusableMinedFoundation(true);
	test.getBoard().spawnMines();
	test.getBoard().getFoundation({ 3, 3 }).setMined(true);
	test.addPylon(std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	test.addPylon(std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	test.addPylon(std::make_pair(4, 5), Pylon::Type::Single, Pylon::Color::Red);
	test.addPylon(std::make_pair(5, 5), Pylon::Type::Single, Pylon::Color::Red);
	test.addPylon(std::make_pair(4, 6), Pylon::Type::Single, Pylon::Color::Red);
	test.addBridge(std::make_pair(3, 3), std::make_pair(4, 5));
	test.addBridge(std::make_pair(3, 4), std::make_pair(4, 6));
	test.addBridge(std::make_pair(4, 3), std::make_pair(5, 5));
	test.getBoard().removePylon({ 2,3 });
	test.addPylon(std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	test.addBridge(std::make_pair(3, 3), std::make_pair(4, 5));
	test.moveBob();

	test.printBoard();
	return 0;
}