#pragma once
#include <iostream>
#include "Game.h"
#include "Utilities.h"

namespace twixt
{
	class GameLoader
	{
	public:
		GameLoader(Game&);
		void saveGame(std::ostream&);
		void loadGame(std::istream&);

	private:
		std::reference_wrapper<Game> m_game;
	};
}
