// iota.h - input iterator 0, 1, 2, ...
#pragma once
#include "input.h"

namespace iter {

	template<class T>
	class iota : public input_base<T*, T> {
		T t;
	public:
		iota(T t = 0)
			: t(t)
		{ }

		T operator*() const
		{
			return t;
		}
		iota& operator++()
		{
			++t;

			return *this;
		}
		iota operator++(int)
		{
			iota i_(*this);

			operator++();

			return i_;
		}
	};

} // iter

#ifdef _DEBUG
#include <cassert>

using iter::iota;

inline void test_iota()
{
	iota<int> i;

	assert (*i == 0);
	assert (*++i == 1);
	i++;
	assert (*i == 2);
}

#endif // _DEBUG