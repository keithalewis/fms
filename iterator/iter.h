// iter.h
#pragma once
#include <stdexcept>
#include "apply.h"
#include "concatenate.h"
#include "constant.h"
#include "choose.h"
#include "enumerator.h"
#include "expr.h"
#include "factorial.h"
#include "input.h"
#include "iota.h"
#include "pair.h"
#include "pow.h"
#include "skip.h"
#include "sum.h"
/*
#include "sequence.h"
*/

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_iterator()
{
	int a[] = {1,2,3};
	assert (10 == sum(e(a,3)*ri(a + 3)));
}

#endif // _DEBUG