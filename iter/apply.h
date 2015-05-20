// apply.h - apply a function to enumerator values
#pragma once
#include <functional>
#include "enumerator.h"
#include "iota.h"

namespace iter {

	// f(*i[0]), f(*i[1]), ...
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of<F(T)>::type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class apply_ : public enumerator<I,U,C> {
		std::function<U(T)> f;
	public:
//		typedef U value_type;
		using enumerator<I,U,C>::i;

		apply_()
		{ }
		apply_(F f, I i)
			: enumerator<I,U,C>(i), f(f)
		{ }

		operator bool() const
		{
			return i;
		}
		U operator*() const
		{
			return f(*i);
		}
		apply_& operator++()
		{
			++i;

			return *this;
		}
		apply_ operator++(int)
		{
			apply_ a(*this);

			operator++();

			return a;
		}
	};
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of<F(T)>::type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto apply(F f, I i)
	{
		return apply_<F,I,T,U,C>(f, i);
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
	auto b = apply([](int i) { return i*i; }, a);
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
		auto i = apply([](double x) { return exp(x); }, a);
		//  this should work!!!
		//auto i = apply(+exp, a);
		ensure (*i++ == exp(0));
		ensure (*i++ == exp(1));
		ensure (*i++ == exp(2));
	}

}

#endif // _DEBUG