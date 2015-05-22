// ftap.cpp - test ftap functions
#include <iostream>
#include "ftap.h"

int main(void)
{
	try {
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}