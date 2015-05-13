// iter.h
#pragma once
#include <stdexcept>
#include "accumulate.h"
#include "apply.h"
#include "concatenate.h"
#include "constant.h"
#include "choose.h"
#include "enumerator.h"
#include "expr.h"
#include "factorial.h"
//#include "input.h"
#include "iota.h"
#include "last.h"
#include "pair.h"
#include "pow.h"
#include "skip.h"
#include "take.h"

/*
#include "sequence.h"
*/

#ifdef _DEBUG
#include <cassert>
#include <cmath>

using namespace iter;

inline void test_iterator()
{
	int a[] = {1,2,3};
	assert (1*3 + 2*2 + 3*1 == back(sum(e(a,3)*ri(a + 3))));

	// sum  1/n!
	double e1 = back(sum(e(c(1)/factorial<>{})));
	double e2 = exp(1);
	double de = e1 - e2;
	assert (fabs(de) <= 2*std::numeric_limits<double>::epsilon());

	e1 = 1 + back(sum(e(prod(c(1)/iota<>(1)))));
	assert (de == e1 - e2);
}

#endif // _DEBUG