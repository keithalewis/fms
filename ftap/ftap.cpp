// ftap.cpp - test ftap functions
#include <iostream>
//#include "ftap.h"
#include "timeseries.h"

using namespace timeseries;

int main(void)
{
	try {
		test_forward_iterator();
		test_apply();
		test_pair();
	}
	catch (...) {
		return -1;
	}

	return 0;
}