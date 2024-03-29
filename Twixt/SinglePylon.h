#pragma once

#include "../ObserverPtr/Pylon.h"

namespace twixt
{
	class SinglePylon : public Pylon
	{
	private:

	public:
		SinglePylon() = delete;
		SinglePylon(const Position&, Color, Type, uint8_t, bool);
		SinglePylon(const SinglePylon&);
		~SinglePylon() = default;

		bool canAddBridge(const Position&) const;
		bool addBridge(nonstd::observer_ptr<Bridge>, const Position&);
		void removeBridge(nonstd::observer_ptr<Bridge>) override;

	};
}