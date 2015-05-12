// exp.h - Exponential function
#pragma once
#include "../iter/iter.h"

namespace math {

	template<class X = double>
	inline X exp(const X& x)
	{
		using iter::e;
		using iter::pow;
		using iter::sum;

		auto n_ = iter::factorial<X>{};

		return sum(e(pow<X>(x)/n_));
	}

} // math

#ifdef _DEBUG
#include <random>

template<class X = double>
inline void test_exp()
{
	X e1 = math::exp(X(1));
	X e1_ = exp(X(1));
	assert (fabs(e1 - e1_) <= 2*std::numeric_limits<X>::epsilon());

	std::default_random_engine dre;
	std::uniform_real_distribution<X> u;

	X max = -std::numeric_limits<X>::max();
	X min = std::numeric_limits<X>::max();
	for (int i = 0; i < 1000; ++i) {
		X x = 1/u(dre); // slash distribution
//		X x = X(i);
		X me = math::exp(x);
		X e = exp(x);
		X de = me - e;

		if (de/e < min)
			min = de/e;
		if (de/e > max)
			max = de/e;
	}

	X y = max - min;
}

#endif // _DEBUG