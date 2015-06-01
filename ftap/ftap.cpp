// ftap.cpp - test ftap functions
#include <iostream>
#include "binomial.h"

int main(void)
{
	try {
		test_binomial();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}