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
#include "include/ensure.h"

inline void test_take() {
	int a[] = {0,1,2};
	auto b = take(2, a);
	ensure (*b == 0);
	ensure (*b == 0);
	++b;
	ensure (*b == 1);
	++b;
	ensure (!b);

	auto c = take(-2, e(a,3));
	ensure (*c == 1);
	++c;
	ensure (*c == 2);
	++c;
	ensure (!c);
}

#endif // _DEBUG