// nomial.h - polynomial evaluation
#pragma once
#include "iter/iter.h"

namespace poly {

	// sum c[n] x^n
	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X nomial(C c, const X& x)
	{
		// static_assert(C::is_counted::value, "poly::nomial: coefficients must be counted");

		return sum0(c*pow(x));
	}


} // poly

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_nomial()
{
	int a[] = {1,2,3};
	ensure (poly::nomial(ce(a), 4) == 1 + 2*4 + 3*4*4);
}


#endif // _DEBUG