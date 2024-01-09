#pragma once

#include "../ObserverPtr/Pylon2.h"

namespace twixt
{
	class SquarePylon : public Pylon
	{
	public:
		SquarePylon() = delete;
		SquarePylon(const Position&, Color, Type, uint8_t, bool);
		SquarePylon(const SquarePylon&);
		~SquarePylon() = default;

		bool canAddBridge(const Position&) const;
		bool addBridge(nonstd::observer_ptr<Bridge>, const Position&);
		void removeBridge(nonstd::observer_ptr<Bridge>) override;
	};
}
