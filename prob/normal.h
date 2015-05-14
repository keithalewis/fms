// normal.h - normal distribution
#pragma once
#include <cmath>
#include "../math/exp.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
// template<typename T> constexpr T M_SQRT2 = sqrt(T(2));
#ifndef M_SQRT2 
#define M_SQRT2 1.41421356237309504880
#endif
// template<typename T> constexpr T M_SQRT2PI = sqrt(2*M_PI<T>);
#ifndef M_SQRT2PI
#define M_SQRT2PI 2.50662827463100050242
#endif

#define pi  M_PI
#define sqrt2pi  M_SQRT2PI

namespace prob {

	template<class X = double>
	struct normal {

		// 0.5 + exp(-x*x/2) sum x^{2n + 1}/(2n + 1)!!
		static X cdf(const X& x)
		{
			using iter::c;
			using iter::iota;
			using iter::pick;
			using iter::pow;
			using iter::sum;
			using math::exp;

			// 2n + 1
			auto n = c(2)*iota(X(0)) + c(1); 

			// not correct !!!
			return X(0.5); // + exp(-x*x/2)*sum(e(pick(prod(c(x)/n),n)))/sqrt2pi;
		}
		static X pdf(const X& x)
		{
			using math::exp;

			exp(-x*x/2)/sqrt2pi;
		}
	};

} // prob

#ifdef _DEBUG
#include <cassert>

using namespace prob;

inline void test_normal()
{
	auto x = normal<>::cdf(0);
	assert (x == 0.5);
	x = normal<>::cdf(1);

}

#endif // _DEBUG