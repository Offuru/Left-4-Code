#pragma once
#include <fstream>
#include <ranges>

#include "Game.h"
#include "Utilities.h"

namespace twixt
{
	class GameLoader
	{
	public:
		GameLoader(Game&);
		void saveGame(const std::string&);
		void loadGame(const std::string&);

	private:
		std::reference_wrapper<Game> m_game;
	};
}
