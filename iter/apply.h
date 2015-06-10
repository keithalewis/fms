// apply.h - apply a function to enumerator values
#pragma once
#include <functional>
#include "enumerator.h"
#include "iota.h"

namespace iter {

	// f(*i0), f(*i1), ...
	template<class F, class I>
	class apply_ : public I {
		typedef typename std::iterator_traits<I>::value_type T;
		typedef typename std::result_of<F(T)>::type U;

		F f;
	public:
		apply_()
		{ }
		apply_(const F& f, I i)
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
		return apply(f, iota<int>(0));
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_apply()
{
	int a[] = {0,1,2};
	auto b = apply(std::function<int(int)>([](int i) { return i*i; }), e(a));
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

//	auto f = [](int n) { return 1 + n + n*n; };
	struct f {
		int operator()(int n) const { return 1 + n + n*n; }
	};
	f F{};
	auto d = apply(F);
	ensure (*d == F(0));
	ensure (*++d == F(1));
	++d;
	ensure (*d == F(2));
	
	{
		struct sq {
			int operator()(int i) { return i*i; }
		};
/*		double a[] = {0,1,2};
		auto i = apply(???, e(a));
		ensure (*i++ == exp(0));
		ensure (*i++ == exp(1));
		ensure (*i++ == exp(2));
		ensure (i); // not counted
*/	}
/*	{
		double a[] = {0,1,2};
		auto i = apply(exp, a);
		ensure (*i++ == exp(0));
		ensure (*i++ == exp(1));
		ensure (*i++ == exp(2));
		ensure (!i); // counted
	}
*/
}

#endif // _DEBUG