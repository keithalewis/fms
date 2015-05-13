// last.h - last item in an enumeration
#pragma once
#include <utility>

namespace iter {

	/// iterate to end
	template<class E>
	inline E last(E e)
	{
		E l(e);

		while (e)
			l = e++;

		return l;
	}
	template<class E>
	inline typename std::iterator_traits<E>::value_type back(E e)
	{
		return *last(e);
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