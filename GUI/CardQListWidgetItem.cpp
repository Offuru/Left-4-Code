#include "CardQListWidgetItem.h"

CardQListWidgetItem::CardQListWidgetItem(Card::Effect effect)
{
	m_cardEffect = effect;
	switch (m_cardEffect)
	{
		case Card::Effect::Draw:
			setText("Draw a card");
			break;
		case Card::Effect::RemoveCards:
			setText("Remove cards");
			break;
		case Card::Effect::RemovePylon:
			setText("Remove pylons");
			break;
		case Card::Effect::RemoveBridge:
			setText("Remove bridges");
			break;
		case Card::Effect::Place2Pylons:
			setText("Place 2 pylons");
			break;
		case Card::Effect::PlaceSquare:
			setText("Place square pylon");
			break;
		case Card::Effect::PlaceCross:
			setText("Place cross pylon");
			break;
		case Card::Effect::MoveBob:
			setText("Move Bob");
			break;
		case Card::Effect::PlaceMine:
			setText("Place mine");
			break;
		default:
			break;
	}
}

Card::Effect CardQListWidgetItem::getEffect()
{
	return m_cardEffect;
}

void CardQListWidgetItem::setEffect(const Card::Effect& effect)
{
	m_cardEffect = effect;
}
