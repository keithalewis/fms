// last.h - last item in an enumeration
#pragma once
#include <utility>

namespace iter {

	template<class E>
	inline E last(E e)
	{
		E l(e);

		while (e)
			l = e++;

		return l;
	}

} // iter

#ifdef _DEBUG
#include <cassert>
#include "enumerator.h"

inline void test_last() {
	int a[] = {0,1,2};

	assert (*iter::last(e(a,3)) == 2);
}

#endif // _DEBUG