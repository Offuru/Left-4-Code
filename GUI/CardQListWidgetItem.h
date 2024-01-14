#pragma once

#include <QListWidgetItem>
#include "Card.h"

class CardQListWidgetItem  : public QListWidgetItem
{
public:
	CardQListWidgetItem(twixt::Card::Effect effect);
	~CardQListWidgetItem() = default;

	twixt::Card::Effect getEffect();
	void setEffect(const twixt::Card::Effect& effect);

private:
	twixt::Card::Effect m_cardEffect;
};
