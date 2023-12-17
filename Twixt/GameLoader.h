#pragma once
#include <fstream>

namespace twixt
{
	class GameLoader
	{
	public:
		static void saveGame();
		static void loadeGame(std::ofstream&);

	};
}
