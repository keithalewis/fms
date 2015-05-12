// hermite.h - Hermite polynomials
#pragma once
#include <functional>
#include <vector>

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
		static std::vector<std::function<X(X)>> H_;

		if (n >= H_.size()) {
			size_t _n = H_.size();
			H_.resize(n+1);
			do {
				H_[_n] = Hermite(_n);
			} while (++_n < n + 1);
		}

		return H_[n];
	};

} // poly

#ifdef _DEBUG
#include <cassert>

using namespace poly;

inline void test_hermite()
{
	for (double x = -10; x <= 10; x += .1) {
		assert (Hermite(0)(x) == 1);
		assert (Hermite(1)(x) == x);
		assert (Hermite(2)(x) == x*x - 1);
		assert (Hermite(3)(x) == x*(x*x - 1) - 2*x);
		assert (Hermite(4)(x) == x*(x*(x*x - 1) - 2*x) - 3*(x*x - 1));
	}

	for (int i = 9; i >= 0; --i) {
		for (double x = -10; x <= 10; x += .1) {
			assert (H(i)(x) == Hermite(i)(x));
		}
	}
}

#endif // _DEBUG