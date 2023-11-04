#pragma once
#include "Pylon.h"
class CrossPylon : public Pylon
{
public:
	CrossPylon() = delete;
	CrossPylon(const Foundation&, Color);
	CrossPylon(const CrossPylon&) = delete;
	~CrossPylon() = default;

	bool canAddBridge(const Foundation&) const;
	bool addBridge(Bridge*, const Foundation&);
private:

};

