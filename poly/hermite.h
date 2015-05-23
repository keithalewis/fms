// hermite.h - Hermite polynomials
// Copyright (c) 2015 KALX, LLC. All rights reserved. No warranty made.
#pragma once
#include <functional>
#include <map>

namespace poly {

	// H(n + 1, x) = x H(n, x) - n H(n - 1, x)
	template<class X = double>
	inline std::function<X(X)> Hermite(size_t n)
	{
		if (n == 0)
			return [](const X& x) { return 1; };
		if (n == 1)
			return [](const X& x) { return x; };
			
		return [n](const X& x) { return x*Hermite(n - 1)(x) - (n - 1)*Hermite(n-2)(x); };
	}

	// memoize
	template<class X = double>
	static std::function<X(X)> H(size_t n) 
	{
		static std::map<size_t,std::function<X(const X&)>> H_;

		auto Hn = H_.find(n);

		return Hn == H_.end() ? H_[n] = Hermite(n) : Hn->second;
	};

} // poly

#ifdef _DEBUG
#include "include/ensure.h"

using namespace poly;

inline void test_hermite()
{
	for (double x = -10; x <= 10; x += .1) {
		ensure (Hermite(0)(x) == 1);
		ensure (Hermite(1)(x) == x);
		ensure (Hermite(2)(x) == x*x - 1);
		ensure (Hermite(3)(x) == x*(x*x - 1) - 2*x);
		ensure (Hermite(4)(x) == x*(x*(x*x - 1) - 2*x) - 3*(x*x - 1));
	}

	for (int i = 9; i >= 0; --i) {
		for (double x = -10; x <= 10; x += .1) {
			ensure (H(i)(x) == Hermite(i)(x));
		}
	}
}

#endif // _DEBUG