// bell.h - Complete Bell polynomials
#pragma once
#include <vector>
#include "../iter/iter.h"

namespace poly {

	// B(n + 1, x[0], ... x[n]) = sum { choose(n,k)*B(n-k,x[0],...,x[n-k])*x[k+1] : 0 <= k <= n }
	template<class X = double>
	X Bell(size_t n, const X* x)
	{
		using iter::choose;
		using iter::sum;
		using iter::ri; // reverse input
		using iter::i;

		if (n == 0)
			return 1;

		std::vector<X> b(n + 1);
		b[0] = X(1);

		for (size_t k = 1; k <= n; ++k)
			b[k] = sum(choose<>(k-1) * ri(&b[k]) * i(x));

		return b[n];
	}

} // bell

#ifdef _DEBUG
#include <cassert>
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

inline void test_bell()
{
	using poly::Bell;

	default_random_engine dre;
	uniform_real_distribution<> u(-1,1);
	vector<double> x(9,1);

	// http://en.wikipedia.org/wiki/Bell_number
	assert (Bell<>(0, &x[0]) == 1);
	assert (Bell<>(1, &x[0]) == 1);
	assert (Bell<>(2, &x[0]) == 2);
	assert (Bell<>(3, &x[0]) == 5);
	assert (Bell<>(4, &x[0]) == 15);
	assert (Bell<>(5, &x[0]) == 52);
	assert (Bell<>(6, &x[0]) == 203);
	assert (Bell<>(7, &x[0]) == 877);
	assert (Bell<>(8, &x[0]) == 4140);

	generate(begin(x), end(x), [&dre,u](void) { return u(dre); });
}

#endif // _DEBUG