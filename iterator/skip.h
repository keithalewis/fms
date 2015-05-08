// skip.h
#pragma once

namespace iterator {

	template<class I>
	inline I skip(I i, size_t n)
	{
		while (n--)
			++i;

		return i;
	}

} // iterator

#ifdef _DEBUG
#include <cassert>

inline void test_skip() {
	int a[] = {0,1,2};

	assert (*skip(a,2) == 2);
}

#endif // _DEBUG