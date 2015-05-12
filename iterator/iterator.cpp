// iterator.cpp
#include <cassert>
#include "iterator.h"

using namespace iterator;

template<class I>
inline typename I::value_type sum(I i, size_t n = 1000)
{
	typename I::value_type s = 0;

	while (n-- && (*i == 0 || 1 + *i != 1))
		s += *i++;

	return s;
}

int main() 
{
	try {
		auto n_ = factorial<double>{};
		auto _1 = constant<double>(1);

		auto s = _1/n_;
		assert (*s == 1);
		assert (*++s == 1);
		assert (*++s == 1/2.);
		assert (*++s == 1/6.);

		auto e = sum(_1/n_);
		double f = e - exp(1);
		assert (fabs(f) <= 2*std::numeric_limits<double>::epsilon());
		f = sum(constant<>(1)/factorial<>{});;

		double x = 2;
		auto expx = sum(iterator::pow<double>(x)/factorial<>{});
		f = exp(2.) - expx;

		test_apply();
		test_choose();
		test_concatenate();
		test_constant();
		test_enumerator();
		test_expr();
		test_factorial();
		test_input();
		test_iota();
		test_pair();
		test_pow();
		test_skip();
		/*
//		test_sequence();
		*/

/*		
*/	}
	catch (...) {
		return -1;
	}

	return 0;
}