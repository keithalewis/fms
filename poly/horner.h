// horner.h - Evaluate polynomial using Horner method
#pragma once
#include "iter/iter.h"

namespace poly {

	// c[0] + x(c[1] + ... + x(c[n-2] + x*c[n-1])...)
	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X horner(C c, const X& x)
	{
		// accumulate reverse iterator from the end
		return back(accumulate([x](const X& a, const X& b) { return a*x + b; }, rend(c), X(0)));
	}

} // poly

#ifdef _DEBUG
#include "include/ensure.h"
#include "nomial.h"

inline void test_horner()
{
	int c[] = {1,2,3};

	ensure (poly::horner(ce(c), 4) == poly::nomial(ce(c), 4));
}


#endif // _DEBUG