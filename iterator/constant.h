// constant.h - constant input iterator
#pragma once
#include "input.h"

namespace iterator {

	template<class T = double>
	class constant : public input_base<const T*,T> {
		T t;
	public:
//		using input_base<const T*,T>::input_base;

		constant(const T& t = 0)
			: t(t)
		{ }
		constant(const constant& c) = default;
		constant& operator=(const constant& c) = default;
		constant(constant&& c) = default;
		constant& operator=(constant&& c) = default;
		~constant()
		{ }

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
	// instead of make_constant
	template<class T>
	inline constant<T> c(const T& t)
	{
		return constant<T>(t);
	}
} // iterator

#ifdef _DEBUG
#include <cassert>

using namespace iterator;

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