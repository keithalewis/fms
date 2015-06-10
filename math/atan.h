// atan.h - arctangent
#pragma once

namespace math {

	// atan(x) = sum_0^oo (2^{2n}(n!)^2/(2n + 1)!) x^{2n+1}/(1 + x^2)^{n+1}
	//	= sum_0   prod  (2/iota(1))*(2/iota(1))   x^2/(1 + x^2) * x/(1 + x^2)
	template<class X>
	inline X atan(const X& x)
	{
		return 0;
	}

} //math