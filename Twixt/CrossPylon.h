#pragma once

#include "Pylon.h"

namespace twixt
{
	class Pylon;

	class CrossPylon : public Pylon
	{
	public:
		CrossPylon() = delete;
		CrossPylon(const Position&, Color, Type);
		CrossPylon(const CrossPylon&);
		~CrossPylon() = default;

		bool canAddBridge(const Position&) const;
		bool addBridge(nonstd::observer_ptr<Bridge>, const Position&);
		void removeBridge(nonstd::observer_ptr<Bridge>) override;

	};
}
