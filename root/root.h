// root.h - root finding
#pragma once

namespace root {

	namespace next {
		
		template<class X = double>
		inline X bisect(const X& x, const X& x_)
		{
			return (x + x_)/X(2);
		}
		template<class X = double, class Y = double>
		inline X newton(const X& x, const Y& y, const decltype(y/x)& m)
		{
			return x - y/m;
		}
		template<class X = double, class Y = double>
		inline X secant(const X& x, const Y& y, const X& x_, const Y& y_)
		{
			auto m = (y - y_)/(x - x_);

			return newton(x, y, m);
		}

	} // next

	namespace done {
		template<class X = double>
		inline bool absolute(const X& x, const X& x_, const X& epsilon)
		{
			return fabs(x - x_) <= epsilon;
		}

	} // done

	template<class N, class D, class X = double, class Y = double>
	inline X find(N next, D done, std::function<Y(X)> f, X x0)
	{
		while (!done()) {
			x0 = next(x0);
		}

		return x0;
	}
	
} // root