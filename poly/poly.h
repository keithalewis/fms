// poly.h - polynomial functions
#pragma once
#if defined(_MSC_VER ) // Visual Studio
#pragma warning(disable: 4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#endif 

#include "bell.h"
#include "hermite.h"

namespace poly {

	// sum c[i] x^i
	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X nomial(iter::counted_enumerator<C> c, const X& x)
	{
		using iter::back;
		using iter::pow;
		using iter::sum;

		return back(sum(c, pow(x)));
	}

	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X horner(C c, const X& x)
	{
		using iter::accumulate;
		using iter::back;
		using iter::rend;

		return back(accumulate([x](const X& a, const X& b) { return a*x + b; }, rend(c), X(0)));
	}
}

#ifdef _DEBUG
#include <cassert>

inline void test_poly()
{
	int c[] = {1,2,3};
	auto ec = e(c,3);
	assert (poly::nomial(ec, 4) == 1 + 2*4 + 3*4*4);
//	assert (poly::horner(ec, 4) == poly::nomial(ec, 4));
}


#endif // _DEBUG