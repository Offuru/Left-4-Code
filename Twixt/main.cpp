#include <iostream>
#include "Game.h"

using namespace twixt;

int main()
{
	Game test;
	test.setReusableMinedFoundation(true);
	test.setExplodeSingleLocation(true);
	test.setExplodeCol(true);
	test.setExplodeRow(true);
	test.setExplodeArea(true);
	test.getBoard().spawnMines();
	test.addPylon(::std::make_pair(2, 19), Pylon::Type::Cross, Pylon::Color::Black);
	test.addPylon(::std::make_pair(3, 13), Pylon::Type::Cross, Pylon::Color::Red);
	test.printBoard();
	::std::cout << "\n\n";
	test.getBoard().getFoundation({ 12, 12 }).setMined(true);
	test.printBoard();
	::std::cout << "\n\n";
	test.addPylon(::std::make_pair(12, 12), Pylon::Type::Cross, Pylon::Color::Red);
	//test.addPylon(::std::make_pair(4, 5), Pylon::Type::Single, Pylon::Color::Red);
	//test.addPylon(::std::make_pair(5, 5), Pylon::Type::Single, Pylon::Color::Red);
	//test.addPylon(::std::make_pair(4, 6), Pylon::Type::Single, Pylon::Color::Red);
	//test.addBridge(::std::make_pair(3, 3), ::std::make_pair(4, 5));
	//test.addBridge(::std::make_pair(3, 4), ::std::make_pair(4, 6));
	//test.addBridge(::std::make_pair(4, 3), ::std::make_pair(5, 5));
	//test.getBoard().removePylon({ 2,3 });
	//test.addPylon(::std::make_pair(3, 3), Pylon::Type::Cross, Pylon::Color::Red);
	//test.addBridge(::std::make_pair(3, 3), ::std::make_pair(4, 5));
	////test.moveBob();
	//test.removeBridge( { 4,5 },{ 3,3 });
	//test.addBridge(::std::make_pair(4, 3), ::std::make_pair(5, 5));
	test.printBoard();
	return 0;
}