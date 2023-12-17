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
			: m_data{ other.get() }
		{}

		explicit observer_ptr(T* pointer) :
			m_data{ pointer }
		{}

		constexpr T* release() noexcept;
		constexpr void reset(T* = nullptr) noexcept;

		constexpr void swap(observer_ptr&) noexcept;
		constexpr friend void swap(observer_ptr& left, observer_ptr& right) noexcept;

		[[nodiscard]] constexpr T* get() const noexcept;
		[[nodiscard]] constexpr operator bool() const noexcept;
		[[nodiscard]] constexpr T* operator->() const noexcept;
		[[nodiscard]] constexpr std::add_lvalue_reference_t<T> operator*() const;
		[[nodiscard]] constexpr explicit operator T* () const noexcept;


	private:
		T* m_data = nullptr;

	};

	//define of member functions
	template<typename T>
	inline constexpr T* observer_ptr<T>::release() noexcept
	{
		return std::exchange(m_data, nullptr);
	}

	template<typename T>
	inline constexpr void observer_ptr<T>::reset(T* ptr) noexcept
	{
		m_data = ptr;
	}

	template<typename T>
	inline constexpr void observer_ptr<T>::swap(observer_ptr& other) noexcept
	{
		std::swap(m_data, other.m_data);
	}

	template<typename T>
	inline constexpr T* observer_ptr<T>::get() const noexcept
	{
		return m_data;
	}

	template<typename T>
	inline constexpr observer_ptr<T>::operator bool() const noexcept
	{
		return m_data != nullptr;
	}

	template<typename T>
	inline constexpr T* observer_ptr<T>::operator->() const noexcept
	{
		return get();
	}

	template<typename T>
	inline constexpr std::add_lvalue_reference_t<T> observer_ptr<T>::operator*() const
	{
		return *get();
	}

	template<typename T>
	inline constexpr observer_ptr<T>::operator T* () const noexcept
	{
		return get();
	}

	template<typename T>
	constexpr void swap(observer_ptr<T>& left, observer_ptr<T>& right) noexcept
	{
		left.swap(right);
	}


	//define of non-member functions
	template<typename T>
	[[nodiscard]] observer_ptr<T> make_observer(T* ptr) noexcept
	{
		return observer_ptr<T>(ptr);
	}

	template<typename T1, typename T2>
	[[nodiscard]] bool operator==(const observer_ptr<T1>& p1, const observer_ptr<T2>& p2)
	{
		return p1.get() == p2.get();
	}

	template<typename T1, typename T2>
	[[nodiscard]] bool operator !=(const observer_ptr<T1>& p1, const observer_ptr<T2>& p2)
	{
		return !(p1 == p2);
	}

	template<typename T>
	[[nodiscard]] bool operator==(const observer_ptr<T>& p, std::nullptr_t) noexcept
	{
		return !static_cast<bool>(p);
	}

	template<typename T>
	[[nodiscard]] bool operator==(std::nullptr_t, const observer_ptr<T>& p) noexcept
	{
		return !static_cast<bool>(p);
	}

	template<typename T>
	[[nodiscard]] bool operator!=(const observer_ptr<T>& p, std::nullptr_t) noexcept
	{
		return p;
	}

	template<typename T>
	[[nodiscard]] bool operator!=(std::nullptr_t, const observer_ptr<T>& p) noexcept
	{
		return p;
	}

	template<typename T1, typename T2>
	[[nodiscard]] bool operator<(const observer_ptr<T1>& p1, const observer_ptr<T2>& p2)
	{
		return std::less<typename std::common_type<T1*, T2*>::type>()(p1.get(), p2.get());
	}

	template<typename T1, typename T2>
	[[nodiscard]] bool operator>(const observer_ptr<T1>& p1, const observer_ptr<T2>& p2)
	{
		return p2 < p1;
	}

	template <typename T1, typename T2>
	[[nodiscard]] bool operator<=(observer_ptr<T1> const& p1, observer_ptr<T2> const& p2)
	{
		return !(p2 < p1);
	}

	template <typename T1, typename T2>
	[[nodiscard]] bool operator>=(observer_ptr<T1> const& p1, observer_ptr<T2> const& p2)
	{
		return !(p1 < p2);
	}
}

namespace std
{
	template<typename T>
	struct hash<::nonstd::observer_ptr<T>>
	{
		size_t operator()(::nonstd::observer_ptr<T> p) const noexcept
		{
			return hash<T*>()(p.get());
		}
	};
}