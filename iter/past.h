// past.h - move iterator past a value
#pragma once
namespace iter {

	template<class T, class I>
	inline I past(const T& t, I i)
	{
		while (i && *i <= t)
			++i;

		return i;
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_past()
{
	int a[] = { 1,2,3 };

	auto b = iter::past(2, a);
	ensure (*b == 3);

	auto c = iter::past(3, ce(a));
	ensure (!c);
}

#endif // _DEBUG
