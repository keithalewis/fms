// take.h - take elements from front or back of enumerator
#pragma once
#include "enumerator.h"
#include "skip.h"

namespace iter {

	template<class N, class I>
	inline counted_enumerator<I> take(N n, I i)
	{
		if (n >= 0)
			return e(i, n);

		while (skipn(-n, i))
			++i;

		return e(i, -n);;
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_take() {
	int a[] = {0,1,2};
	auto b = take(2, a);
	assert (*b == 0);
	assert (*b == 0);
	++b;
	assert (*b == 1);
	++b;
	assert (!b);

	auto c = take(-2, e(a,3));
	assert (*c == 1);
	++c;
	assert (*c == 2);
	++c;
	assert (!c);
}

#endif // _DEBUG