#include "HumanPlayer.h"
#include <iostream>
#include <sstream>
#include <regex>

using namespace twixt;

twixt::HumanPlayer::HumanPlayer(const std::string& name) : IPlayer(name)
{}

HumanPlayer& HumanPlayer::operator=(const HumanPlayer& other)
{
	m_name = other.m_name;
	m_color = other.m_color;
	m_noBridges = other.m_noBridges;
	m_noPylons1x1 = other.m_noPylons1x1;
	m_noPylons2x2 = other.m_noPylons2x2;
	m_noPylonsCross = other.m_noPylonsCross;

	return *this;
}

HumanPlayer::Move twixt::HumanPlayer::getNextMove()
{
	std::cout <<getName() << ", input your next move: "; //TO DO?: move to game to 
									  //prevent multiple printing 
									  //(adding/moving multiple bridges, invalid move)
	std::vector<uint8_t> input;

	std::string line;

	Move move;

	std::regex numberReg{ R"(\d+)" };

	std::getline(std::cin, line);
	if (line == "")
		std::getline(std::cin, line);

	std::smatch match;
	while (std::regex_search(line, match, numberReg))
	{
		input.push_back(std::stoi(match[0].str()));
		line = match.suffix().str();
	}

	switch (input.size())
	{
	case 3:
		return { static_cast<Action>(input[0]), {input[1],input[2]}, std::nullopt };
	case 5:
		return { static_cast<Action>(input[0]), {input[1],input[2]}, std::optional<Position>({input[3],input[4]}) };
	default:
		return {};
		break;
	}
}
