// apply.h - apply a function to enumerator values
#pragma once
#include <functional>
#include "enumerator.h"
#include "iota.h"

namespace iter {

	// f(*i[0]), f(*i[1]), ...
	template<class F, class I>
	class apply_ : public I {
		typedef typename std::iterator_traits<I>::value_type T;
		typedef typename std::result_of<F(T)>::type U;

		std::function<U(T)> f;
	public:
		apply_()
		{ }
		apply_(F f, I i)
			: I(i), f(f)
		{ }

		explicit operator bool() const
		{
			return I::operator bool();
		}
		U operator*() const
		{
			return f(I::operator*());
		}
		apply_& operator++()
		{
			I::operator++();

			return *this;
		}
		apply_ operator++(int)
		{
			apply_ a(*this);

			operator++();

			return a;
		}
	};
	template<class F, class I>
	inline auto apply(F f, I i)
	{
		return apply_<F,I>(f, i);
	}
	// f[0], f[1], ...
	template<class F>
	inline auto apply(F f)
	{
		return apply(f, iota<size_t>());
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_apply()
{
	int a[] = {0,1,2};
	auto b = apply([](int i) { return i*i; }, e(a));
	decltype(b) c;
	c = b;
	ensure (*b == 0);
	ensure (*++b == 1);
	b++;
	ensure (*b == 4);

	ensure (*c == 0);
	ensure (*++c == 1);
	c++;
	ensure (*c == 4);

	auto f = [](int n) { return 1 + n + n*n; };
	auto d = apply(f);
	ensure (*d == f(0));
	ensure (*++d == f(1));
	++d;
	ensure (*d == f(2));
	
	{
		double a[] = {0,1,2};
		auto i = apply([](double x) { return exp(x); }, e(a));
		//  this should work!!!
		//auto i = apply(+exp, a);
		ensure (*i++ == exp(0));
		ensure (*i++ == exp(1));
		ensure (*i++ == exp(2));
		ensure (i); // not counted
	}
	{
		double a[] = {0,1,2};
		auto i = apply([](double x) { return exp(x); }, ce(a,3));
		//  this should work!!!
		//auto i = apply(+exp, a);
		ensure (*i++ == exp(0));
		ensure (*i++ == exp(1));
		ensure (*i++ == exp(2));
		ensure (!i); // counted
	}

}

#endif // _DEBUG