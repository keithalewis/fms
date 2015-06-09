// iter.h
#pragma once
#if defined(_MSC_VER ) // Visual Studio
#pragma warning(disable: 4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#endif 

#include <stdexcept>
#include "enumerator.h"
#include "enumerator/counted.h"
#include "enumerator/end.h"
#include "enumerator/null.h"
#include "enumerator/reverse.h"
#include "pair.h"
#include "expr.h"
#include "accumulate.h"
#include "adjacent.h"
#include "apply.h"
#include "buffer.h"
#include "choose.h"
#include "concatenate.h"
#include "constant.h"
#include "cycle.h"
#include "elide.h"
#include "factorial.h"
#include "fmap.h"
#include "iota.h"
#include "level.h"
#include "join.h"
#include "last.h"
#include "past.h"
#include "pick.h"
#include "pow.h"
#include "skip.h"
#include "take.h"
#include "unit.h"
#include "upto.h"
#include "util.h"
#include "where.h"
#include "zigg.h"
/*
#include "bind.h"
#include "enumerator.h"
*/

#ifdef _DEBUG
#include "include/ensure.h"
#include <cmath>

using namespace iter;

inline void test_iterator()
{
	int i = 1;
	auto ci = c(i);
	static_assert (sizeof(i) == sizeof(ci), "time for a new compiler");

	int a[] = {1,2,3};
	ensure (1*3 + 2*2 + 3*1 == 
		back( // last element
		 sum( // running sum
		  ce(a) // counted iterator with 3 elements
		  *      // + - * / any enumerators
		  re(a + 3) // reverse enumerator
		 )
		)
	);

	// sum  1/n!
	double e1 = exp(1);
	// 1 + 1/1 + 1/2! ...
	double e2 = back(sum(ne(c(1)/factorial<double>())));
	//                   ^ - terminate when 1/n! less than machine epsilon.
	double de = e1 - e2;
	ensure (fabs(de) <= 2*std::numeric_limits<double>::epsilon());

	// 1 + 1/1 + (1/1)*(1/2) ...
	e2 = 1 + sum0(ne(prod(c(1)/iota(1.0))));
	ensure (de == e1 - e2);

	auto id = [](int n) { return n; };
	auto eq = equal_to(iota(0), apply(std::function<int(int)>(id)));
	ensure (all(ce(eq,10)));

	ensure (all(take(10, iota(1))));
	ensure (any(take(10, iota(0))));

}

#endif // _DEBUG