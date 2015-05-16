// iter.cpp
#include "include/ensure.h"
#include "iter.h"

using namespace iter;

inline void test_poly()
{
	int a[] = {1,2,3};
	auto xn = pow(4);
	auto p = ce(a)*xn;
	auto s = sum(p);
	auto f = back(s);
	ensure (f == 1 + 2*4 + 3*4*4);
	ensure (back(sum(ce(a)*pow(4))) == 1 + 2*4 + 3*4*4);
}

int main() 
{
	try {
		test_poly();

		test_accumulate();
		test_adjacent();
		test_apply();
		test_choose();
		test_concatenate();
		test_constant();
		test_enumerator();
		test_enumerator_counted();
		test_enumerator_end();
		test_enumerator_null();
		test_enumerator_reverse();
		test_expr();
		test_factorial();
		test_fmap();
		test_iterator();
		test_iota();
		test_last();
		test_pick();
		test_pair();
		test_pow();
		test_skip();
		test_take();
		test_where();

	}
	catch (...) {
		return -1;
	}

	return 0;
}
