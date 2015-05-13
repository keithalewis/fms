// constant.h - constant input iterator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T = double>
	class constant_ : public enumerator_base<const T*,T> {
		T t;
	public:
		// defaults so infinite
		constant_(const T& t = 0)
			: t(t)
		{ }

		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return t;
		}
		constant_& operator++()
		{
			return *this;
		}
		constant_ operator++(int)
		{
			return *this;
		}
	};
	template<class T>
	inline constant_<T> constant(const T& t)
	{
		return constant_<T>(t);
	}
	// shorthand
	template<class T>
	inline constant_<T> c(const T& t)
	{
		return constant_<T>(t);
	}
} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_constant()
{
	constant_<int> zero;
	assert (*zero == 0);
	assert (*++zero == 0);
	assert (*zero++ == 0);

	constant_<int> two(2);
	assert (*two == 2);
	assert (*++two == 2);
	assert (*two++ == 2);

	auto four = c(4);
	assert (*four++ == 4 && *++four == 4);
}

#endif // _DEBUG