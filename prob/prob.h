// prob.h - probability related functionality
#pragma once

namespace prob {

	template<class P, class X = double>
	inline X inv(const X& x)
	{
		return root1d<X>([=x](const X& p) { return P::cdf(y) - x; }, x);
	}

} // prob