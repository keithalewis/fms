// normal_.h - perturb cumulants of normal distribution
#pragma once
#include "poly/bell.h"
#include "poly/hermite.h"
#include "normal.h"

namespace prob {

	// N_(x) = N(x) - (exp(-x^2/2)/sqrt(2pi)) sum_1 B_n(x_1,...,x_k) H_{n-1}(x)/k!
	template<class X = double>
	struct normal_ {
		template<class K>
		static X cdf(const X& x, K kappa)
		{
			auto B = apply([kappa](int n) { return Bell(n, kappa); }, iota(1));
			auto H_ = apply([x](int n) { return H(n)(x); }, iota(0));

			return normal<X>::cdf(x) - X(0.5)*exp(-x*x/2)*sum0(ne(B*H_/factorial()))/sqrt2pi;
		}
	};

} // prob