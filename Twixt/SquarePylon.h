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
		bool addBridge(nonstd::observer_ptr<Bridge>, const Position&);
		void removeBridge(nonstd::observer_ptr<Bridge>) override;
	};
}
