// include.cpp - test include files
#include <iostream>
#include "timer.h"

int main()
{
	try {
		test_timer();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}