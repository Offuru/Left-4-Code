#pragma once
#include <type_traits>
#include <memory>

namespace nonstd
{
	template<typename T>
	class observer_ptr
	{
	public:
		constexpr observer_ptr() noexcept {};
		constexpr observer_ptr(std::nullptr_t) noexcept {};

		template <typename U, typename = std::enable_if_t<std::is_convertible_v<U*, T*>>>
		observer_ptr(observer_ptr<U> other) noexcept
		{}

		explicit observer_ptr(T* pointer) :
			data{ pointer }
		{}

	private:
		T* data = nullptr;

	};
}