// constant.h - constant input iterator
#pragma once
#include "input.h"

namespace iterator {

	template<class T>
	class constant : public input<const T*,T> {
		T t;
	public:
		using input<const T*,T>::input;

		constant(const T& t = 0)
			: t(t)
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
}

#endif // _DEBUG