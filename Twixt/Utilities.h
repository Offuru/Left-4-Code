#pragma once
#include<climits>
#include<memory>

namespace twixt 
{
	using Position = std::pair<uint8_t, uint8_t>;

	template<class Derived,class Base>
	bool instanceOf(Derived* derived)
	{
		return dynamic_cast<Base*>(derived) != nullptr;
	}
}
