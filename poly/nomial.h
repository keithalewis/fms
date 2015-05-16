// nomial.h - polynomial evaluation
#pragma once
#include "iter/iter.h"

namespace poly {

	// sum c[n] x^n
	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X nomial(C c, const X& x)
	{
		return back(sum(c*pow(x)));
	}
/*
	template<class X, size_t N, class C = X>
	struct poly_ {
		template<C c0, C... c_>
		X nomial(const X& x)
		{
			return c0 + x*nomial<c_...>(x);
		}
		template<C c0>
		X nomial(const X& x)
		{
			return c0;
		}
	};
*/
} // poly

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_nomial()
{
	int a[] = {1,2,3};
	ensure (poly::nomial(ce(a), 4) == 1 + 2*4 + 3*4*4);
}


#endif // _DEBUG