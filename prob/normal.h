// normal.h - normal distribution
#pragma once
#include <cmath>

namespace prob {

	template<class X = double>
	struct normal {
		constexpr X pi = 4*atan(X(1));
		constexpr X sqrt2pi = sqrt(2*pi);

		// 0.5 + exp(-x*x/2) sum x^{2n + 1}/(2n + 1)!!
		static X cdf(const X& x)
		{
			return 0;
		}
		static X pdf(const X& x)
		{
			exp(-x*x/2)/sqrt2pi;
		}
	};

} // prob