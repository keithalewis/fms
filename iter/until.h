// until.h - increment until a condition is met
#pragma once

namespace iter {

	template<class P, class I>
	inline I until(const P& p, I i)
	{
		while (i && !p(i))
			++i;

		return i;
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_until()
{
	int a[] = {1,2,3};

	auto b = until([](auto i) { return *i == 2; }, a);
	ensure (*b == 2);

	auto c = until([](auto) { return false; }, ce(a));
	ensure (c == a + 3);
}

#endif // _DEBUG