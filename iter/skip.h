// skip.h
#pragma once
#include <utility>

namespace iter {

	template<class I, class N>
	inline I skip(I i, N n)
	{
		std::advance(i, n);

		return i;
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_skip() {
	int a[] = {0,1,2};

	assert (*skip(a,2) == 2);
}

#endif // _DEBUG