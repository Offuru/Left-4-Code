#pragma once

#include "Pylon.h"

class SquarePylon : public Pylon
{
public:
	SquarePylon() = delete;
	SquarePylon(const Foundation&, Color);
	SquarePylon(const SquarePylon&) = delete;
	~SquarePylon() = default;

	bool canAddBridge(const Foundation&) const;
	bool addBridge(Bridge*, const Foundation&);
private:

};

