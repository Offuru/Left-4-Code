#include "CardQListWidgetItem.h"

CardQListWidgetItem::CardQListWidgetItem(twixt::Card::Effect effect)
{
	m_cardEffect = effect;
	switch (m_cardEffect)
	{
		case twixt::Card::Effect::Draw:
			setText("Draw two cards");
			break;
		case twixt::Card::Effect::RemoveCards:
			setText("Remove enemy cards");
			break;
		case twixt::Card::Effect::RemovePylon:
			setText("Remove enemy pylon");
			break;
		case twixt::Card::Effect::RemoveBridge:
			setText("Remove enemy bridge");
			break;
		case twixt::Card::Effect::Place2Pylons:
			setText("Place 2 pylons");
			break;
		case twixt::Card::Effect::PlaceSquare:
			setText("Place square pylon");
			break;
		case twixt::Card::Effect::PlaceCross:
			setText("Place cross pylon");
			break;
		case twixt::Card::Effect::MoveBob:
			setText("Move Bob");
			break;
		case twixt::Card::Effect::PlaceMine:
			setText("Place mine");
			break;
		default:
			break;
	}
}

twixt::Card::Effect CardQListWidgetItem::getEffect()
{
	return m_cardEffect;
}

void CardQListWidgetItem::setEffect(const twixt::Card::Effect& effect)
{
	m_cardEffect = effect;
}
