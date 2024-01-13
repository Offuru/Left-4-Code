#pragma once

#include <QListWidgetItem>
#include "Card.h"

class CardQListWidgetItem  : public QListWidgetItem
{
public:
	CardQListWidgetItem(Card::Effect effect);
	~CardQListWidgetItem() = default;

	Card::Effect getEffect();
	void setEffect(const Card::Effect& effect);

private:
	Card::Effect m_cardEffect;
};
