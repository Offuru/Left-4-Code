#pragma once
#include "Pylon.h"
#include "IPlayer.h"

namespace twixt
{
	class HumanPlayer: public IPlayer
	{
	private:

	public:

		HumanPlayer() = default;
		HumanPlayer(const std::string& name);
		HumanPlayer(const HumanPlayer&) = default;
		~HumanPlayer() = default;
		HumanPlayer& operator=(const HumanPlayer&);

		Move getNextMove() override;

	};
}
