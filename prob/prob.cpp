// prob.cpp - test probability project
#include <cassert>
#include "prob.h"

int main(void)
{
	try {
		test_cumulant();
		test_normal();
	}
	catch (...) {
		return -1;
	}

	return 0;
}