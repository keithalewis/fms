// bell.h - Complete Bell polynomials
#pragma once
#include <vector>
#include "../iterator/iterator.h"

namespace poly {

	// B(n + 1, x[0], ... x[n]) = sum { choose(n,k)*B(n-k,x[0],...,x[n-k])*x[k+1] : 0 <= k <= n }
	template<class X = double>
	X Bell(size_t n, const X* x)
	{
		using iterator::choose;
		using iterator::sum;
		using iterator::ri;
		using iterator::i;

		if (n == 0)
			return 1;

		std::vector<X> b(n) = {X(1)};

		for (size_t k = 1; k < n; ++k)
			b[k] = sum(choose(k-1) * ri(&b[k]) * i(x));

		return b[n-1];
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
	vector<double> x(9);

	generate(begin(x), end(x), [&dre,u](void) { return u(dre); });

	assert (Bell<>(0, &x[0]) == 1);
}

#endif // _DEBUG