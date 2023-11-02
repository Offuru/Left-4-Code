#pragma once

#include "Pylon.h"

class SinglePylon : public Pylon
{
private:

public:
	SinglePylon() = delete;
	SinglePylon(const Foundation&, Color);
	SinglePylon(const SinglePylon&) = delete;
	~SinglePylon() = default;

	void addBridge(Bridge*);
};

