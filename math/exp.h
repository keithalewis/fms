// exp.h - Exponential function
#pragma once
#include "../iter/iter.h"

namespace math {

	// sum_0 x^n/n!
	template<class X = double>
	inline X exp(const X& x)
	{
		return X(1 + sum0(ne(prod(c(x)/iota(X(1))))));
	}

} // math

#ifdef _DEBUG
#include <ctime>
#include <random>
#include "include/ensure.h"
//#include "include/timer.h"

template<class X = double>
inline void test_exp()
{
	{
		auto a = ne(prod(pow(1.)/iota(1.)));
		auto b = buffer(0,a);
		b = skipn(100,b);
		++b;
	}
	long long c;
/*	auto 
	ms = timer::time([]() { exp(0.1); }, 10*1000*1000);
	c = ms.count();
	ms = timer::time([]() { math::exp(0.1); }, 10*1000);
	c = ms.count();

	X e1 = math::exp(X(1));
	X e1_ = exp(X(1));
	ensure (fabs(e1 - e1_) <= 2*std::numeric_limits<X>::epsilon());
*/
	std::default_random_engine dre;
	std::uniform_real_distribution<X> u(-18,18); //

	dre.seed(static_cast<unsigned long>(std::time(nullptr)));

	X max = -std::numeric_limits<X>::max();
	X min = std::numeric_limits<X>::max();
	for (int i = 0; i < 1000; ++i) {
		X x = u(dre);
//		X x = X(i);
		X me = math::exp(x);
		X e = exp(x);
		X de = me - e;

		if (de/e < min)
			min = de/e;
		if (de/e > max)
			max = de/e;
	}
	ensure (0*max < 10*std::numeric_limits<X>::epsilon());
	ensure (0*min > -12*std::numeric_limits<X>::epsilon());
}

#endif // _DEBUG