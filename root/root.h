// root.h - policy based root finding
#pragma once
#include <cmath>
#include <functional>
#include <tuple>
#include "iter/iter.h"

namespace root1d {

	template<class X = double>
	struct point {
		X x, y;
	};

	// x is in (min(a,b), max(a,b))
	template<class X>
	inline bool between(const X& x, const X& a, const X& b)
	{
		return signbit(x - a) != signbit(x - b);
	}

	// convergence criteria
	template<class X>
	inline bool delta(const point<X>& p, const point<X>& p_,
		const X& abs = 2*std::numeric_limits<X>::epsilon(),
		const X& rel = 0)
	{
		return fabs(p.x - p_.x) <= abs + rel*fabs(p_.x); 
	}

	template<class X>
	inline bool residual(const point<X>& p, const point<X>& p_,
		const X& abs = std::numeric_limits<X>::epsilon(),
		const X& rel = 0)
	{
		return fabs(p.y) >= fabs(p_.y) && fabs(p_.y) < abs + rel*fabs(p_.y);
	}

	// try to improve by moving one ULP at a time
	template<class F, class X = double>
	inline X tweek(const F& f, const X& x, const X& dx)
	{
		X y = f(x);

		X x_ = nextafter(x, x + dx);
		X y_ = f(x_);

		if (fabs(y_) < fabs(y))
			return tweek(f, x_, dx);

		return x;
	}
	template<class F, class X = double>
	inline X tweek(const F& f, const X& x)
	{
		X x_ = tweek(f, x, X(1));

		if (x_ == x) // try other direction
			x_ = tweek(f, x, X(-1));

		return x_;
	}

	// returns the pair bracketing the root
	template<class X>
	inline std::tuple<point<X>,point<X>> 
	false_position(const std::tuple<point<X>,point<X>,point<X>>& p)
	{
		const point<X>& p0 = std::get<0>(p);
		const point<X>& p1 = std::get<1>(p);
		const point<X>& p2 = std::get<2>(p);

		// first two must be bracketed
		ensure (signbit(p0.y) != signbit(p1.y));

		// most recent estimates bracket
		if (signbit(p1.y) != signbit(p2.y))
			return std::make_tuple(p1, p2);

		ensure (signbit(p0.y) != signbit(p2.y));

		// false position slowness
		return std::make_tuple(p0, p2);
	}

	template<class F, class X = double>
	struct secant {
		F f;
		point<X> p;
		X m; // slope

		secant()
		{ }
		secant(F f, point<X> p, X m)
			: f(f), p(p), m(m)
		{ }

		secant& next()
		{
			point<X> p_;
			
			p_.x = p.x - p.y/m;
			p_.y = f(p_.x);
			m = (p_.y - p.y)/(p_.x - p.x);

			std::swap(p_, p);

			return *this;
		}
		secant next(int) const
		{
			secant s(*this);

			s.next();

			return s;
		}
	};
/*
	template<class F, class X = double>
	inline xym<X> kahan(const F& f, const xym<X>& p0)
	{
		xym<X> p1 = secant(f, p0);
		xym<X> p2 = secant(f, p1);

		if (signbit(p0.y) != signbit(p1.y)) { 
			// don't allow root to become unbracketed
			if (signbit(p1.y) != signbit(p2.y)) {
				X r = 0;//(p0.x - p2.x)/(p
			}
		}

		return p2;
	}
*/

	// m is best guess at f'(x)
	template<class F, class X = double>
	inline X solve(F f, X x, X m)
	{
		secant<F,X> s(f, point<X>{x,f(x)}, m), s_;

		do {
			s_ = s.next(0);
			std::swap(s, s_);
		} while (fabs(s.p.x - s_.p.x) > 4 * std::numeric_limits<X>::epsilon());

		return s_.p.x;
	}

} // root1d

#ifdef _DEBUG
inline void test_next()
{
	using namespace root1d;

	ensure (between(2.,1.,3.));
	ensure (between(2.,3.,1.));
	ensure (between(-2.,-1.,-3.));
	ensure (between(-2.,-3.,-1.));
	ensure (!between(2.,-3.,-1.));

	struct sqr {
		double a;
		sqr(double a = 0) : a(a) { }
		double operator()(double x) const
		{ return x*x - a; }
	};

	double a = 2;
	auto f = sqr(a);
	double r = solve(f, 1., 2.);
	r = tweek(f, r);
//	r = solve([a](double x) { return x*x - a; }, 2., 4.);
	r = r;
}

#endif // _DEBUG