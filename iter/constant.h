// constant.h - constant input iterator
#pragma once
#include "input.h"

namespace iter {

	template<class T = double>
	class constant : public enumerator_base<const T*,T> {
		T t;
		mutable size_t n;
	public:
		// defaults so infinite
		constant(const T& t = 0, size_t n = 0)
			: t(t), n(n)
		{ }

		operator T*() const
		{
			return &t;
		}
		operator bool() const
		{
			return --n != 0;
		}
		T operator*() const
		{
			return t;
		}
		constant& operator++()
		{
			return *this;
		}
		constant operator++(int)
		{
			return *this;
		}
	};
	template<class T>
	inline constant<T> make_constant(const T& t)
	{
		return constant<T>(t);
	}
	// shorthand
	template<class T>
	inline constant<T> c(const T& t)
	{
		return constant<T>(t);
	}
} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_constant()
{
	constant<int> zero;
	assert (*zero == 0);
	assert (*++zero == 0);
	assert (*zero++ == 0);

	constant<int> two(2);
	assert (*two == 2);
	assert (*++two == 2);
	assert (*two++ == 2);

	auto four = c(4);
	assert (*four++ == 4 && *++four == 4);
}

#endif // _DEBUG