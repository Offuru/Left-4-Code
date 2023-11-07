#pragma once

#include "Pylon.h"

class SinglePylon : public Pylon
{
private:

public:
	SinglePylon() = delete;
	SinglePylon(const Position&, Color, Type);
	SinglePylon(const SinglePylon&);
	~SinglePylon() = default;

	bool canAddBridge(const Position&) const;
	bool addBridge(Bridge*, const Position&);
};

