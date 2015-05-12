// hermite.h - Hermite polynomials
#pragma once
#include <functional>
#include <vector>

namespace poly {

	template<class X = double>
	inline std::function<X(X)> hermite(size_t n)
	{
		switch (n) {
		case 0:
			return [](const X& x) { return 1; };
		case 1:
			return [](const X& x) { return x; };
		}

		return [n](const X& x) { return x*hermite(n - 1)(x) - (n - 1)*hermite(n-2)(x); };
	}
	// iota to instantiate
	static std::vector<std::function<double(double)>> H{
		hermite<>(0),
		hermite<>(1)
	};

} // poly

#ifdef _DEBUG
#include <cassert>

using namespace poly;

inline void test_hermite()
{
	for (double x = -10; x <= 10; x += .1) {
		assert (hermite(0)(x) == 1);
		assert (hermite(1)(x) == x);
		assert (hermite(2)(x) == x*x - 1);
		assert (hermite(3)(x) == x*(x*x - 1) - 2*x);
		assert (hermite(4)(x) == x*(x*(x*x - 1) - 2*x) - 3*(x*x - 1));
	}
}

#endif // _DEBUG