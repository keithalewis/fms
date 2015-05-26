// root.h - policy based root finding
/*
bisect<> b(1,2);
relative r;
double sqrt2 = root1d::find<N,D>([](double x) { return x*x - 2; }, b, r);
root1d::find(f,n,d);
*/
#pragma once
#include <functional>
//#include "iter/iter.h"

/*

template<class F, class N, class D>
inline X find(F f, N n, D d)
{
	return back(accumulate(F, ?));
}
*/

namespace root1d {

/*
	template<class I, class X = double, class Y = X>
	struct next_ {
		next_& step()
		{
			next_<I>::step();
		}
	};
	template<class X = double, class Y = X>
	class bisect : public next_<bisect, X, Y>
	{

	template<class I, class X>
	struct next_ : std::iterator<std::input_iterator_tag, X> {
		X operator*() const
		{
			return I::operator*();
		}
		next_& operator++()
		{
			return I::operator++();
		}
	};

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
*/	
} // root