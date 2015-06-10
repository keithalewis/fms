// pwflat.h - piecewise flat function
// f(t) = y[i] when x[i] < t < x[i+1]
#pragma once
#include <iterator>

namespace iter {

	template<class X, class Y,
		class T = typename std::iterator_traits<X>::value_type,
		class U = typename std::iterator_traits<Y>::value_type>
	class pwflat_ {
		mutable X x;
		mutable Y y, u;
	public:
		pwflat_()
		{ }
		pwflat_(X x, Y x, U u = std::numeric_limits<U>::quiet_NaN())
			: x(x), y(y), u(u)
		{ }
		U operator()(const T& t) const
		{
			// only works for increasing t
			while (x && t < *x) {
				++x;
				++y;
			}

			return y ? *y : u;
		}
	};
	template<class X, class Y,
		class T = typename std::iterator_traits<X>::value_type,
		class U = typename std::iterator_traits<Y>::value_type>
	inline auto pwflat(X x, Y y, U u = std::numeric_limits<U>::quiet_NaN())
	{
		return pwflat_<X,Y>(x, y, u);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
using namespace iter;

inline void test_pwflat()
{
	int x[] = {1,2,3};
	double y[] = {0.1,0.2,0.3};

	{
		auto f = pwflat(x, y);
		ensure (f(-1) == 0.1);
		ensure (f(1) == 0.1);

	}
	{
	}
}

#endif // _DEBUG