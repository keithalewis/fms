// until.h - increment until a condition is met
#pragma once

namespace iter {

	template<class P, class I>
	inline I until(P p, I i)
	{
		while (!p(i))
			++i;

		return i;
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_until()
{
	int a[] = {1,2,3};

	auto b = until([](int* i) { return *i == 2; }, a);
	ensure (*b == 2);
}

#endif // _DEBUG