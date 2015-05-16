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
#include "include/ensure.h"

inline void test_pick()
{
	int a[] = {0,1,2,3,4,5};
	int i[] = {2,3,5};
	auto b = pick(i, a);
	ensure (*b++ == 2);
	ensure (*b == 3);
	ensure (*++b == 5);
}

#endif // _DEBUG