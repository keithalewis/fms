// bspline.h - basis splines
#pragma once
#include <iterator>

namespace poly {

	// B_i,0(x) = 1(t_i <= x < t_{i+1})
	// B_i,k(x) = B_i,k-1(x) (x - t_i)/(t_{i+k} - t_i) + B_{i+1},k-1(x) (t_{i+k+1} - x)/(t_{i+k+1} - t_{i+1})
	//	t_i <= x < t_{i + k + 1}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline T bspline(size_t i, size_t k, I t, T x)
	{
		if (t[i] > x || x >= t[i+k+1])
			return T(0);

		if (k == 0)
			return T(1);

		T u = (x - t[i])/(t[i+k] - t[i]);
		T v = (t[i+k+1] - x)/(t[i+k+1] - t[i+1]);

		return bspline(i, k-1, t, x)*u + bspline(i+1, k-1, t, x)*v;
	}
	/*
	// b-spline of order k with coefficients c
	template<class C, class I, class T = std::iterator_traits<I>::value_type>
	inline auto bspline(C c, size_t k, I t)
	{
		return [c,k,t](const T& x) {
			T s{0};

			for (size_t i = 0; c; ++i, ++c)
				s += (*c)*bspline(i,k,t,x);

			return s;
		};
	}
	*/
} // poly
#ifdef _DEBUG
#include "include/ensure.h"
#include "iter/enumerator.h"
using namespace poly;

inline void test_bspline()
{
	{
		double t[] = {0,1,2};
		auto f0 = [t](size_t i, double x) { return bspline(i, 0, iter::ce(t), x); };
		ensure (f0(0,-1) == 0);
		ensure (f0(0,0) == 1);
		ensure (f0(0,.5) == 1);
		ensure (f0(0,1) == 0);
		ensure (f0(0,1.1) == 0);
	}
}

#endif // _DEBUG