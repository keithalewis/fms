// dual.cpp - dual number tests
#include <iostream>
#include "dual.h"

int main()
{
	try {
		test_dual_number<>();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}