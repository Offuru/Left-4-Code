#include "GameLoader.h"

using namespace twixt;

twixt::GameLoader::GameLoader(Game& game) :
	m_game{ game }
{}


void twixt::GameLoader::loadGame(std::istream& in)
{

}

/*
dimensiunea tablei
bool m_humanPlayers;
m_bigPylons;
m_minedFundations;
m_explodeSingleLocation;
m_explodeCol;
m_explodeRow;
m_explodeArea;
m_reusableMinedFoundation;
m_debuilderBob;
m_cards;
player names 
current color

cardDeck
locatiia lui bob
locatia minelor

bridge & pylon remaining

piloni (tip, culoare, rotatie, bigConfig)
bridge (culoare, foundatie1 pos, fundatie2 pos)


*/
void twixt::GameLoader::saveGame(std::ostream& out)
{
	out << m_game.get().getHumanPlayers() << '\n';
	out << m_game.get().getBigPylons() << '\n';
	out << m_game.get().getExplodeSingleLocation() << '\n';
	out << m_game.get().getExplodeCol() << '\n';
	out << m_game.get().getExplodeRow() << '\n';
	out << m_game.get().getExplodeArea() << '\n';
	out << m_game.get().getReusableMinedFoundation() << '\n';
	out << m_game.get().getDebuilderBob() << '\n';
	out << m_game.get().getCards() << '\n';

	out << m_game.get().getPlayer1().get()->getName() << '\n';
	out << m_game.get().getPlayer1().get()->getTypeString() << '\n';
	out << m_game.get().getPlayer1().get()->getNoPylons1x1() << ' ';
	out << m_game.get().getPlayer1().get()->getNoPylons2x2() << ' ';
	out << m_game.get().getPlayer1().get()->getNoPylonsCross() << ' ';
	out << m_game.get().getPlayer1().get()->getNoBridges() << '\n';
	out << m_game.get().getPlayer1().get()->getCards().size() << '\n';
	for (const auto& card : m_game.get().getPlayer1().get()->getCards())
	{
		out << card.getEffectString() << ' ';
	}
	out << '\n';

	out << m_game.get().getPlayer2().get()->getName() << '\n';
	out << m_game.get().getPlayer2().get()->getTypeString() << '\n';
	out << m_game.get().getPlayer2().get()->getNoPylons1x1() << ' ';
	out << m_game.get().getPlayer2().get()->getNoPylons2x2() << ' ';
	out << m_game.get().getPlayer2().get()->getNoPylonsCross() << ' ';
	out << m_game.get().getPlayer2().get()->getNoBridges() << '\n';
	out << m_game.get().getPlayer2().get()->getCards().size() << '\n';
	for (const auto& card : m_game.get().getPlayer2().get()->getCards())
	{
		out << card.getEffectString() << ' ';
	}
	out << '\n';

	out << m_game.get().getCardDeck().size() << ' ';
	for (const auto& card : m_game.get().getCardDeck())
	{
		out << card.getEffectString() << ' ';
	}
	out << '\n';

	out << m_game.get().getBob().getPosition().first << ' ' << m_game.get().getBob().getPosition().second << '\n';

	out << m_game.get().getBoard().getSize() << '\n';
	for (const auto& line : m_game.get().getBoard().getBoard())
	{
		for (const auto& foundation : line)
		{
			out << foundation.getMined() << ' ' << foundation.getExploded() << '\n';
		}
	}

	out << m_game.get().getBoard().getPylons().size() << '\n';
	for (const auto& pylon : m_game.get().getBoard().getPylons())
	{
		out << pylon.first.first << ' ' << pylon.first.second << ' ' << static_cast<int>(pylon.second.get()->getColor()) << ' ' << static_cast<int>(pylon.second.get()->getType()) << ' ' << pylon.second.get()->getPylonRotation() << ' ' << pylon.second.get()->getBigConfiguration() << '\n';
	}

	out << m_game.get().getBoard().getBridges().size() << '\n';
	for (const auto& bridge : m_game.get().getBoard().getBridges())
	{
		out << bridge.get()->getPosStart().first << ' ' << bridge.get()->getPosStart().second << ' ' << bridge.get()->getPosEnd().first << ' ' << bridge.get()->getPosEnd().second << static_cast<bool>(bridge.get()->getPylonStart().get()->getColor()) << '\n';
	}
}
