// range.cpp - test range functions
#include <iostream>
#include "primitives.h"
#include "range.h"
#include "range_apply.h"
#include "range_pair.h"
#include "range_sequence.h"
#include "range_running.h"

using namespace range;

int main(void)
{
	try {
		test_iterator();
		test_enumerator();
		test_concatenate();
		test_apply();
		test_pair();
		test_sequence();
		test_running();
	}
	catch (...) {
		return -1;
	}

	return 0;
}
