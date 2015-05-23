// iter.h
#pragma once
#if defined(_MSC_VER ) // Visual Studio
#pragma warning(disable: 4800) // warning C4800: 'int' : forcing value to bool 'true' or 'false' (performance warning)
#endif 

#include <stdexcept>
#include "accumulate.h"
#include "adjacent.h"
#include "apply.h"
#include "bind.h"
#include "buffer.h"
#include "concatenate.h"
#include "constant.h"
#include "choose.h"
#include "elide.h"
#include "enumerator.h"
#include "enumerator/counted.h"
#include "enumerator/end.h"
#include "enumerator/null.h"
#include "enumerator/reverse.h"
#include "expr.h"
#include "factorial.h"
#include "fmap.h"
#include "iota.h"
#include "join.h"
#include "last.h"
#include "level.h"
#include "pick.h"
#include "pair.h"
#include "pow.h"
#include "skip.h"
#include "take.h"
#include "unit.h"
#include "util.h"
#include "where.h"
#include "zigg.h"

#ifdef _DEBUG
#include "include/ensure.h"
#include <cmath>

using namespace iter;

inline void test_iterator()
{/*
	int i = 1;
	auto ci = c(i);
	ensure (sizeof(i) == sizeof(ci));

	int a[] = {1,2,3};
	ensure (1*3 + 2*2 + 3*1 == 
		back( // last element
		 sum( // running sum
		  e(a,3) // counted iterator with 3 elements
		  *      // + - * / any enumerators
		  re(a + 3) // reverse enumerator
		 )
		)
	);

	// sum  1/n!
	double e1 = exp(1);
	// 1 + 1/1 + 1/2! ...
	double e2 = back(sum(e(c(1)/factorial<double>())));
	//                   ^ - terminate when 1/n! becomes 0.
	double de = e1 - e2;
	ensure (fabs(de) <= 2*std::numeric_limits<double>::epsilon());

	// 1 + 1/1 + (1/1)*(1/2) ...
	e2 = 1 + back(sum(e(prod(c(1)/iota(1.0)))));
	ensure (de == e1 - e2);

	auto id = [](size_t n) { return n; };
	auto eq = equal(iota(0), apply(id));
	ensure (all(e(eq,10)));

	ensure (all(take(10, iota(1))));
	ensure (any(take(10, iota(0))));
	*/
}

#endif // _DEBUG