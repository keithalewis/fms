// poly.h - polynomial functions
#pragma once
#if defined(_MSC_VER ) // Visual Studio
#pragma warning(disable: 4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#endif 

#include "bell.h"
#include "hermite.h"

namespace poly {

	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X nomial(C c, const X& x)
	{
		using iter::back;
		using iter::sum;
		using iter::pow;

		return back(sum(c, pow(x)));
	}

	template<class C, class X = typename std::iterator_traits<C>::value_type>
	inline X horner(C c, const X& x, bool reverse = false)
	{
		using iter::accumulate;
		using iter::back;
		using iter::end;
		using iter::sum;
		using iter::pow;

		return reverse 
			? horner(rend(c), x)
			: back(accumulate([x](const X& a, const X& b) { return a*x + b; }, c, X(0)));
	}
}

#ifdef _DEBUG
#include <cassert>

inline void test_poly()
{
	int c[] = {1,2,3};
	assert (poly::nomial(e(c,3), 4) == 1 + 2*4 + 3*4*4);
	assert (poly::horner(c, 4, true) == poly::nomial(c, 4));
}


#endif // _DEBUG