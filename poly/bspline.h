// bspline.h - basis splines
#pragma once
#include <iterator>

namespace poly {

	// B_i,1(x) = 1(t_i <= x < t_{i+1})
	// B_i,k(x) = B_i,k-1(x) (x - t_i)/(t_{i+k} - t_i) + B_{i+1},k-1(x) (t_{i+k+1} - x)/(t_{i+k+1} - t_{i+1})
	//	t_i <= x < t_{i + k + 1}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline T bspline(size_t i, size_t k, I t, T x)
	{
		if (t[i] > x || x >= t[i+k])
			return T(0);

		if (k == 1)
			return T(1);

		T u = (x - t[i])/(t[i+k-1] - t[i]);
		T v = (t[i+k] - x)/(t[i+k] - t[i+1]);

		return bspline(i, k-1, t, x)*u + bspline(i+1, k-1, t, x)*v;
	}
	
	// b-spline of order k with coefficients c
	template<class C, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto bspline(C c, size_t k, I t)
	{
		return [c,k,t](const T& x) {
			T s{0};
			C c_(c);

			for (size_t i = 0; c_; ++i, ++c_)
				s += (*c_)*bspline(i,k,t,x);

			return s;
		};
	}
	
} // poly
#ifdef _DEBUG
#include "include/ensure.h"
#include "iter/enumerator/counted.h"
#include "iter/constant.h"
using namespace iter;
using namespace poly;

inline void test_bspline()
{
	{
		double t[] = {0,1,2};
		auto f1 = [&t](size_t i, double x) { return bspline(i, 1, ce(t), x); };
		for (int i = 0; i < 2; ++i) {
			ensure(f1(i, i-1) == 0);
			ensure(f1(i, i+0) == 1);
			ensure(f1(i, i+.5) == 1);
			ensure(f1(i, i+1) == 0);
			ensure(f1(i, i+1.1) == 0);
		}

		auto f2 = [&t](size_t i, double x) { return bspline(i, 2, ce(t), x); };
		ensure(f2(0, -1) == 0);
		ensure(f2(0, 0) == 0);
		ensure(f2(0, .5) == .5);
		ensure(f2(0, 1) == 1);
		ensure(f2(0, 1.5) == .5);
		ensure(f2(0, 2) == 0);
		ensure(f2(0, 3) == 0);
	}
	{
		double t[] = { 0,0,1,2,3,4,4 };
		size_t n = sizeof(t) / sizeof(*t);
		size_t k = 2;
		auto C = take(n - k, c(1.));
		auto f = bspline(C, k, t);
		double y, x = 0;
		y = f(x);
		while (x < 3.1) {
			y = f(x);
			x += .5;
		}
	}
}

#endif // _DEBUG