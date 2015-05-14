// pick.h - pick items at increasing locations
#pragma once
#include "adjacent.h"
#include "skip.h"

namespace iter {

	// assumes i is non-decreasing
	// e[i[0]], e[i[1]], ...
	template<class I, class E>
	inline auto pick(I i, E e)
	{
		return skip(delta(i), e);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_pick()
{
	int a[] = {0,1,2,3,4,5};
	int i[] = {2,3,5};
	auto b = pick(i, a);
	assert (*b++ == 2);
	assert (*b == 3);
	assert (*++b == 5);
}

#endif // _DEBUG