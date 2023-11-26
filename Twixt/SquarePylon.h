#pragma once

#include "Pylon.h"

namespace twixt
{
	class SquarePylon : public Pylon
	{
	public:
		SquarePylon() = delete;
		SquarePylon(const Position&, Color, Type);
		SquarePylon(const SquarePylon&);
		~SquarePylon() = default;

		bool canAddBridge(const Position&) const;
		bool addBridge(Bridge*, const Position&);
		void removeBridge(Bridge*) override;
	};
}
