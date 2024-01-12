#include "GameLoader.h"
using namespace twixt;

twixt::GameLoader::GameLoader(Game& game) :
	m_game{ game }
{}


void twixt::GameLoader::loadGame(const std::string& path)
{
	std::ifstream in(path);
	int tmp;
	std::string tmpString1, tmpString2;
	in >> tmp;
	m_game.get().setHumanPlayers(tmp);
	in >> tmp;
	m_game.get().setMinedFoundations(tmp);
	in >> tmp;
	m_game.get().setBigPylons(tmp);
	in >> tmp;
	m_game.get().setExplodeSingleLocation(tmp);
	in >> tmp;
	m_game.get().setExplodeCol(tmp);
	in >> tmp;
	m_game.get().setExplodeCol(tmp);
	in >> tmp;
	m_game.get().setExplodeArea(tmp);
	in >> tmp;
	m_game.get().setReusableMinedFoundation(tmp);
	in >> tmp;
	m_game.get().setDebuilderBob(tmp);
	in >> tmp;
	m_game.get().setCards(tmp);

	in >> tmpString1 >> tmpString2;
	m_game.get().setPlayer1(tmpString1, tmpString2 != "human");
	in >> tmp;
	m_game.get().getPlayer1().get()->setColor(static_cast<twixt::Pylon::Color>(tmp));
	in >> tmp;
	m_game.get().getPlayer1().get()->setNoPylons1x1(tmp);
	if (m_game.get().getBigPylons())
	{
		in >> tmp;
		m_game.get().getPlayer1().get()->setNoPylons2x2(tmp);
		in >> tmp;
		m_game.get().getPlayer1().get()->setNoPylonsCross(tmp);
	}
	in >> tmp;
	m_game.get().getPlayer1().get()->setNoBridges(tmp);
	
	if(m_game.get().getCards())
	{
		auto findEffect = [&tmpString1](const auto& cardEffect) { return cardEffect.second == tmpString1; };
		std::vector<Card>cards;
		in >> tmp;
		for (int i = 0; i < tmp; ++i)
		{
			in >> tmpString1;
			auto effect = std::ranges::find_if(Card::effects, findEffect);
			Card tmpCard{ effect->first };
			cards.push_back(tmpCard);
		}
		m_game.get().getPlayer1().get()->setCards(cards);
		cards.clear();
	}

	in >> tmpString1 >> tmpString2;
	m_game.get().setPlayer2(tmpString1, tmpString2 != "human");
	in >> tmp;
	m_game.get().getPlayer2().get()->setColor(static_cast<twixt::Pylon::Color>(tmp));
	in >> tmp;
	m_game.get().getPlayer2().get()->setNoPylons1x1(tmp);
	if (m_game.get().getBigPylons())
	{
		in >> tmp;
		m_game.get().getPlayer2().get()->setNoPylons2x2(tmp);
		in >> tmp;
		m_game.get().getPlayer2().get()->setNoPylonsCross(tmp);
	}
	in >> tmp;
	m_game.get().getPlayer2().get()->setNoBridges(tmp);
	if (m_game.get().getCards())
	{
		auto findEffect = [&tmpString1](const auto& cardEffect) { return cardEffect.second == tmpString1; };
		std::vector<Card>cards;
		in >> tmp;
		for (int i = 0; i < tmp; ++i)
		{
			in >> tmpString1;
			auto effect = std::ranges::find_if(Card::effects, findEffect);
			Card tmpCard{ effect->first };
			cards.push_back(tmpCard);
		}
		m_game.get().getPlayer2().get()->setCards(cards);
		cards.clear();


		in >> tmp;
		for (int i = 0; i < tmp; ++i)
		{
			in >> tmpString1;
			auto effect = std::ranges::find_if(Card::effects, findEffect);
			Card tmpCard{ effect->first };
			cards.push_back(tmpCard);
		}
		m_game.get().setCardDeck(cards);
		cards.clear();
	}

	if (m_game.get().getDebuilderBob())
	{
		int x, y;
		in >> x >> y;
		m_game.get().getBob().setPosition({ x,y });
	}
	in >> tmp;
	m_game.get().getBoard().setSize(tmp);
	if (m_game.get().getMinedFoundations())
	{
		for ( auto& line : m_game.get().getBoard().getBoard())
		{
			for ( auto& foundation : line)
			{
				in >> tmp;
				foundation.setMined(tmp);
				in >> tmp;
				foundation.setExploded(tmp);
			}
		}
	}
	in >> tmp;
	for (int i = 0; i < tmp; ++i)
	{
		int x, y, color, type, rotation, config;
		in >> x >> y>>color>>type>>rotation>>config;
		m_game.get().addPylon({ x,y }, static_cast<twixt::Pylon::Type>(type), static_cast<twixt::Pylon::Color>(color), rotation, config);
	}
	in >> tmp;
	for (int i = 0; i < tmp; ++i)
	{
		int x1, y1, x2, y2,color;
		in >> x1 >> y1 >> x2 >> y2 >> color;
		m_game.get().addBridge({ x1,y1 }, { x2,y2 }, static_cast<twixt::Pylon::Color>(color));
	}

	in >> tmp;
	if (static_cast<twixt::Pylon::Color>(tmp) == m_game.get().getPlayer1().get()->getColor())
	{
		m_game.get().setCurrentPlayer(nonstd::make_observer<IPlayer>(m_game.get().getPlayer1().get()));
	}
	else
	{
		m_game.get().setCurrentPlayer(nonstd::make_observer<IPlayer>(m_game.get().getPlayer2().get()));
	}
	in >> tmp;
	m_game.get().setRound(tmp);
	in.close();
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
void twixt::GameLoader::saveGame(const std::string& path)
{
	std::ofstream out(path);
	//game flags
	out << m_game.get().getHumanPlayers() << '\n';
	out << m_game.get().getMinedFoundations() << '\n';
	out << m_game.get().getBigPylons() << '\n';
	out << m_game.get().getExplodeSingleLocation() << '\n';
	out << m_game.get().getExplodeCol() << '\n';
	out << m_game.get().getExplodeRow() << '\n';
	out << m_game.get().getExplodeArea() << '\n';
	out << m_game.get().getReusableMinedFoundation() << '\n';
	out << m_game.get().getDebuilderBob() << '\n';
	out << m_game.get().getCards() << '\n';
	//player 1 details
	out << m_game.get().getPlayer1().get()->getName() << '\n';
	out << m_game.get().getPlayer1().get()->getTypeString() << '\n';
	out << static_cast<int>(m_game.get().getPlayer1().get()->getColor()) << '\n';
	out << m_game.get().getPlayer1().get()->getNoPylons1x1() << ' ';
	if(m_game.get().getBigPylons())
	{
		out << m_game.get().getPlayer1().get()->getNoPylons2x2() << ' ';
		out << m_game.get().getPlayer1().get()->getNoPylonsCross() << ' ';
	}
	out << m_game.get().getPlayer1().get()->getNoBridges() << '\n';
	if(m_game.get().getCards())
	{

		out << m_game.get().getPlayer1().get()->getCards().size() << '\n';
		for (const auto& card : m_game.get().getPlayer1().get()->getCards())
		{
			out << card.getEffectString() << ' ';
		}
		out << '\n';
	}
	//player 2 details
	out << m_game.get().getPlayer2().get()->getName() << '\n';
	out << m_game.get().getPlayer2().get()->getTypeString() << '\n';
	out << static_cast<int>(m_game.get().getPlayer2().get()->getColor()) << '\n';
	out << m_game.get().getPlayer2().get()->getNoPylons1x1() << ' ';
	if (m_game.get().getBigPylons())
	{
		out << m_game.get().getPlayer2().get()->getNoPylons2x2() << ' ';
		out << m_game.get().getPlayer2().get()->getNoPylonsCross() << ' ';
	}
	out << m_game.get().getPlayer2().get()->getNoBridges() << '\n';
	if (m_game.get().getCards())
	{
		out << m_game.get().getPlayer2().get()->getCards().size() << '\n';
		for (const auto& card : m_game.get().getPlayer2().get()->getCards())
		{
			out << card.getEffectString() << ' ';
		}
		out << '\n';

		//card deck
		out << m_game.get().getCardDeck().size() << ' ';
		for (const auto& card : m_game.get().getCardDeck())
		{
			out << card.getEffectString() << ' ';
		}
		out << '\n';
	}
	
	if (m_game.get().getDebuilderBob())
	{
		out << m_game.get().getBob().getPosition().first << ' ' << m_game.get().getBob().getPosition().second << '\n';
	}
	//board
	out << m_game.get().getBoard().getSize() << '\n';
	if(m_game.get().getMinedFoundations())
	{
		for (const auto& line : m_game.get().getBoard().getBoard())
		{
			for (const auto& foundation : line)
			{
				out << foundation.getMined() << ' ' << foundation.getExploded() << '\n';
			}
		}
	}
	//pylons
	out << m_game.get().getBoard().getPylons().size() << '\n';
	for (const auto& pylon : m_game.get().getBoard().getPylons())
	{
		out << pylon.first.first << ' ' << pylon.first.second << ' ' << static_cast<int>(pylon.second.get()->getColor()) << ' ' << static_cast<int>(pylon.second.get()->getType()) << ' ' << pylon.second.get()->getPylonRotation() << ' ' << pylon.second.get()->getBigConfiguration() << '\n';
	}
	//bridges
	out << m_game.get().getBoard().getBridges().size() << '\n';
	for (const auto& bridge : m_game.get().getBoard().getBridges())
	{
		out << bridge.get()->getPosStart().first << ' ' << bridge.get()->getPosStart().second << ' ' << bridge.get()->getPosEnd().first << ' ' << bridge.get()->getPosEnd().second << static_cast<bool>(bridge.get()->getPylonStart().get()->getColor()) << '\n';
	}

	out << static_cast<int>(m_game.get().getCurrentPlayer().get()->getColor()) << '\n';
	out << m_game.get().getRound() << '\n';
	out.close();
}
