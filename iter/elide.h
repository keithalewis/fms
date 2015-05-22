// elide.h - remove empty enumerators
#pragma once
#include "where.h"

namespace iter {

	template<class I>
	inline auto elide(I i)
	{
		return where([](const auto& j) { return *j; }, i);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "join.h"
#include "fmap.h"
#include "skip.h"

inline void test_elide()
{
	{
		int a[] = {1,0,2,0,0,3};
		// {{1},{},{2,2},{},{},{3,3,3}}
		auto b = fmap([&](int i) { return ce(c(i),i); }, a);
		// {{1},{2,2},{3,3,3}}
		auto c = elide(b);
		auto d(c);
		c = d;
		auto e = *c;
		ensure (*e == 1);
		ensure (!++e);
		e = *++c;
		ensure (*e == 2);
		ensure (*++e == 2);
		ensure (!++e);
		e = *++c;
		ensure (*e == 3);
		ensure (*++e == 3);
		ensure (*++e == 3);
		ensure (!++e);
	}
	{
		int a[] = {1,0,2,0,0,3};
		auto f = join(elide(fmap([&](int i) { return ce(c(i),i); }, a)));
		ensure (*f == 1);
		ensure (*++f == 2);
		ensure (*++f == 2);
		ensure (*++f == 3);
		ensure (*++f == 3);
		ensure (*++f == 3);
	}
}

#endif // _DEBUG