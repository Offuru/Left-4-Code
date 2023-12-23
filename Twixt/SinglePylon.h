#pragma once

#include "../ObserverPtr/Pylon2.h"

namespace twixt
{
	class SinglePylon : public Pylon
	{
	private:

	public:
		SinglePylon() = delete;
		SinglePylon(const Position&, Color, Type);
		SinglePylon(const SinglePylon&);
		~SinglePylon() = default;

		bool canAddBridge(const Position&) const;
		bool addBridge(nonstd::observer_ptr<Bridge>, const Position&);
		void removeBridge(nonstd::observer_ptr<Bridge>) override;

	};
}