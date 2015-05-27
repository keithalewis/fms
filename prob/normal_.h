// normal_.h - perturb cumulants of normal distribution
#pragma once
#include "poly/bell.h"
#include "poly/hermite.h"
#include "normal.h"

namespace prob {

	// normal with perturbed cumulants
	template<class X = double>
	struct normal_ {
		// N_(x) = N(x) - (exp(-x^2/2)/sqrt(2pi)) sum_1 B_n(x_1,...,x_k) H_{n-1}(x)/k!
		template<class K>
		static X cdf(const X& x, K kappa)
		{
			auto BH_ = bell(kappa)*hermite(x)/factorial(X(1));

			return normal<X>::cdf(x) - X(0.5)*exp(-x*x/2)*sum0(ne(BH_))/sqrt2pi;
		}
		// pdf!!!
	};

} // prob