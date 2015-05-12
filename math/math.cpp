// math.cpp - test math project
#include "math.h"

int main()
{
	try {
		test_exp<double>();
		test_exp<float>();
	}
	catch (...) {
		return -1;
	}

	return 0;
}