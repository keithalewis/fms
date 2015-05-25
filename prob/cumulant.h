// cumlant.h - various cumulants
#pragma once
#include "iter/iter.h"

namespace prob {
namespace cumulant {

	// kappa_n^* = sum_{k>=0} kappa_{n+k} s^k/k!
	template<class K, class X = double>
	inline auto esscher(K kappa, const X& s)
	{
//		auto a = last(ne(kappa*prod(c(s)/iota(X(1)))));

//		return a;
		return map([s](K k) { return last(ne(k*prod(c<X>(s)/iota<X>(X(1))))); }, kappa);
	}

	// (n-1)! mu^n
	template<class X = double>
	inline auto exponential(const X& mu)
	{
		return factorial<X>()*skipn(1, pow<X>(mu));
	}
	// (n-1)! mu^n (1/(1 - mu s)^{n-1} - 1)
	template<class X = double, class S = double>
	inline auto exponential(const X& mu, const S& s)
	{
		return factorial<X>()*skipn(1, pow<X>(mu));
	}

	template<class X = double>
	inline auto poisson(const X& mu)
	{
		return constant(mu);
	}
	template<class X = double, class S = double>
	inline auto poisson(const X& mu, const S& s)
	{
		return constant(mu*(exp(s) - 1));
	}
		
} // cumulant
} // prob
#ifdef _DEBUG
#include "include/ensure.h"

inline void test_cumulant()
{
	using namespace prob;
	using namespace cumulant;

	auto p = poisson(0.1);
	auto p_ = esscher(p, 0.1);

}

#endif // _DEBUG
