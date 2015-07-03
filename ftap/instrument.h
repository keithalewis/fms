// instrument.h - instruments
#pragma once

namespace currency {
	template<class A = void>
	struct USD {
		A amount;
	};
	inline USD<long double> operator"" USD(long double a)
	{
		return USD<long double>{a};
	}
	template<class A = void>
	class EUR {
		A amount;
	};
	inline EUR<long double> operator"" EUR(long double a)
	{
		return EUR<long double>{a};
	}
}
