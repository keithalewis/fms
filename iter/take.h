// take.h - take elements from front or back of enumerator
#pragma once
#include "enumerator.h"
#include "skip.h"

namespace iter {

	template<class N, class I>
	inline counted_enumerator_<I> take(N n, I i)
	{
		if (n >= 0)
			return ce(i, n);

		while (skipn(-n, i))
			++i;

		return ce(i, -n);
	}
	// specialize take for counted_enumerator
	template<class N, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto take(N n, const counted_enumerator_<I,T>& e)
	{
		if (n >= 0)
			return ce(e.iterator(), n);

		auto i = e.end().iterator();
		std::advance(i, n);

		return ce(i, -n);
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

	auto c = take(-2, ce(a,3));
	ensure (*c == 1);
	++c;
	ensure (*c == 2);
	++c;
	ensure (!c);
}

#endif // _DEBUG