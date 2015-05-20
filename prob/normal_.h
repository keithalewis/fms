// normal_.h - perturb cumulants of normal distribution
#pragma once
#include "poly/bell.h"
#include "normal.h"

namespace prob {

	// N_(x) = N(x) - sum_1 B_k(x_1,...,x_k) H_{k-1}(x)/k!
	template<class X = double>
	struct normal_ {
		template<class K>
		static X cdf(const X& x, K kappa)
		{
			auto B = apply([x](int n) { return bell(n, kappa); }, itoa(1));

			return normal::cdf(x) - sum0(0);
		}
	};

} // prob