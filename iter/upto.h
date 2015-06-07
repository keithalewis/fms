// upto.h - move iterator upto a value
#pragma once
namespace iter {

	template<class T, class I>
	inline I upto(T t, I i)
	{
		while (i && *i < t)
			++i;

		return i;
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_upto()
{
	int a[] = { 1,2,3 };

	auto b = iter::upto(2, a);
	ensure(*b == 2);

	auto c = iter::upto(4, ce(a));
	ensure(!c);
}

#endif // _DEBUG

