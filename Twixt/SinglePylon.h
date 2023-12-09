#pragma once

#include "Pylon.h"

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
		bool addBridge(std::shared_ptr<Bridge>, const Position&);
		void removeBridge(std::shared_ptr<Bridge>) override;

	};
}