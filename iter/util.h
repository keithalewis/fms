// util.h - utilites
#pragma once
#include "fmap.h"

// e.g., pick(L(n, 2*n + 1), factorial{}, ) => (2n+1)!
// lambda macro
#ifndef L_
#define L_(x,...) [](auto x) { return (__VA_ARGS__) ; }
#endif
// expressions using n
#ifndef N_
#define N_(...) [](auto n) { return (__VA_ARGS__) ; }
#endif
// enumerator over n
#ifndef E_
#define E_(...) fmap([](auto n) { return (__VA_ARGS__) ; }, iota(0))
#endif

namespace iter {

	template<class I>
	inline bool all(I i)
	{
		while (i) {
			if (0 == *i) 
				return false;
			++i;
		}

		return true;
	}

	template<class I>
	inline bool any(I i)
	{
		while (i) {
			if (0 != *i) 
				return true;
			++i;
		}

		return false;
	}

} // iter
#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_util()
{
	int a[] = {1,2,3};
	auto b = iter::ce(a);
	ensure (all(b));
	ensure (any(b));

	// x -> x*x
	auto c = L_(x, x*x);
	ensure (c(1.2) == 1.2*1.2);

	// n -> n*n
	auto d = N_(n*n);
	ensure (d(2) == 4);

	// 1, 2 + 1, 2*2 + 1, ... 
//	auto f = E_(2*n + 1);
//	ensure (*f == 1);
//	ensure (*++f == 2 + 1);
//	ensure (*++f == 2*2 + 1);
}

#endif // _DEBUG