// root.h - policy based root finding
#pragma once
#include <functional>
#include "iter/iter.h"

namespace root1d {

	template<class X = double, class Y = X>
	struct point {
		X x;
		Y y;
		point(const X& x = X(0), const Y& y = Y(0))
			: x(x), y(y)
		{ }
	};

	// bracketed roots
	template<class F, class X = double, class Y = X>
	class bisect_ : public enumerator_<void,point<X,Y>,std::input_iterator_tag> {
		F f;
		point<X,Y> p0, p1;
	public:
		bisect_()
		{ }
		bisect_(F f, const X& x0, const X& x1)
			: f(f), p0(x0,f(x0)), p1(x1,f(x1))
		{
			ensure (p0.y * p1.y < 0);
		}

		explicit operator bool() const
		{
			return true;
		}
		point<X,Y> operator*() const
		{
			return fabs(p0.y) < fabs(p1.y) ? p0 : p1;
		}
		bisect_& operator++()
		{
			X x = (p0.x + p1.x)/2;
			Y y = f(x);

			if (p0.y * y < 0) {
				p1.x = x;
				p1.y = y;
			}
			else {
				p0.x = x;
				p0.y = y;
			}

			ensure (p0.y*p1.y <= 0);

			return *this;
		}
		bisect_ operator++(int)
		{
			bisect_ b(*this);

			operator++();

			return b;
		}
	};
	template<class F, class X = double, class Y = X>
	inline auto bisect(F f, const X& x0, const X& x1)
	{
		return bisect_<F,X,Y>(f, x0, x1);
	}

/*
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

#ifdef _DEBUG
inline void test_next()
{
	using namespace root1d;
	
	struct sqr {
		double a;
		sqr(double a) : a(a) { }
		double operator()(double x) { return x*x - a; }
	};

	auto b = bisect(sqr(2),1.,2.);
	point<> p;
	p = *b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
	p = *++b;
}

#endif // _DEBUG