// iter.cpp
#include <cassert>
#include "iter.h"

using namespace iter;

int main() 
{
	try {
		test_accumulate();
		test_adjacent();
		test_apply();
		test_choose();
		test_concatenate();
		test_constant();
		test_enumerator();
		test_expr();
		test_factorial();
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