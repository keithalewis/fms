// normal.h - normal distribution
#pragma once
#include <cmath>
#include "iter/iter.h"
#include "math/exp.h"
#include "poly/hermite.h"

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

	class marsaglia {};
	class bell {};
/*
	template<class I>
	inline X std_normal(const X&);

	// 0.5(1 + sgn(x) sqrt(1 - exp(-2 x^2/pi)
	template<>
	inline X std_normal<bell>(const X& x)
	{
		return X(0.5)*(1 + (x > 0 ? 1 : -1)*sqrt(1 - math::exp(-2*x*x/pi)));
	}
*/
	template<class X = double>
	struct normal {

		// 0.5 + exp(-x*x/2) sum x^{2n + 1}/(2n + 1)!!/sqrt2pi
//		template<>
		static X cdf/*<marsaglia>*/(const X& x)
		{
			return X(0.5) + x*sum0(ne(prod(c(x*x)/E_(2*n + 1))))*exp(-x*x/2)/sqrt2pi;
		}
		
		static X pdf(const X& x)
		{
			return math::exp(-x*x/2)/sqrt2pi;
		}
		static X inv(const X& x)
		{
			return 0;
		}
		// n-th derivative
		static X ddf(size_t n, const X& x)
		{
			if (n == 0)
				return cdf(x);
			if (n == 1)
				return pdf(x);

			// (-1)^{n-1}H_{n-1}(x) e^{-x^2/2}/sqrt2pi
			return (n%2?-1:1)*poly::H(n-1)(x)*math::exp(-x*x/2)/sqrt2pi;
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

	ensure (normal<>::cdf(0) == normal<>::ddf(0,0));
	ensure (normal<>::pdf(0) == normal<>::ddf(1,0));
	ensure (0 == normal<>::ddf(2,0));
	ensure (1/sqrt2pi == normal<>::ddf(3,0));
	ensure (-0 == normal<>::ddf(4,0));
	x = normal<>::ddf(5,0);
}

#endif // _DEBUG