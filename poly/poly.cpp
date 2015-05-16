// poly.cpp - test polynomial functions
#include "poly.h"

int main()
{
	try {
		test_bell();
		test_hermite();
		test_horner();
		test_nomial();
	}
	catch (...) {
		return -1;
	}

	return 0;
}