#include "IPlayer.h"

twixt::IPlayer::IPlayer(const std::string& name)
{
	m_name = name;
	m_color = Pylon::Color::Red;
	m_noBridges = 50;
	m_noPylons1x1 = 30;
	m_noPylons2x2 = 5;
	m_noPylonsCross = 5;
}

void twixt::IPlayer::removeCard(size_t index)
{
	if (index < 0 || index > m_cards.size())
		return;

	m_cards.erase(m_cards.begin() + index);
}

void twixt::IPlayer::draw(std::stack<Card>& cards)
{
	m_cards.push_back(cards.top());
	cards.pop();
}

bool twixt::IPlayer::validMove(const Move& nextMove, uint8_t boardSize) const
{
	const auto& [action, pos1, pos2] = nextMove;

	if (action < Action::AddSinglePylon || action > Action::PlayCard)
		return false;
	if (pos1.value().first < 0 || pos1.value().second >= boardSize)
		return false;
	if (pos2.has_value() && (pos2.value().first < 0 || pos2.value().second >= boardSize))
		return false;

	return true;
}

void twixt::IPlayer::setName(const std::string& name)
{
	m_name = name;
}

void twixt::IPlayer::setColor(Pylon::Color color)
{
	m_color = color;
}

void twixt::IPlayer::setNoBridges(uint8_t noBridges)
{
	m_noBridges = noBridges;
}

void twixt::IPlayer::setNoPylons1x1(uint8_t noPylons)
{
	m_noPylons1x1 = noPylons;
}

void twixt::IPlayer::setNoPylons2x2(uint8_t noPylons)
{
	m_noPylons2x2 = noPylons;
}

void twixt::IPlayer::setNoPylonsCross(uint8_t noPylons)
{
	m_noPylonsCross = noPylons;
}

void twixt::IPlayer::setCards(const std::vector<Card>& cards)
{
	m_cards = cards;
}

std::string twixt::IPlayer::getName() const
{
	return m_name;
}

twixt::Pylon::Color twixt::IPlayer::getColor() const
{
	return m_color;
}

uint8_t twixt::IPlayer::getNoBridges() const
{
	return m_noBridges;
}

uint8_t twixt::IPlayer::getNoPylons1x1() const
{
	return m_noPylons1x1;
}

uint8_t twixt::IPlayer::getNoPylons2x2() const
{
	return m_noPylons2x2;
}

uint8_t twixt::IPlayer::getNoPylonsCross() const
{
	return m_noPylonsCross;
}

std::vector<Card> twixt::IPlayer::getCards() const
{
	return m_cards;
}
