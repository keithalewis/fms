// apply.h - apply a function to an iter
#pragma once
#include <functional>
#include "enumerator.h"
#include "iota.h"

namespace iter {

	template<class F, class E, class T = typename std::iterator_traits<E>::value_type,
		class U = typename std::result_of_t<F(T)>>
	class apply_ : public enumerator_base<E,U> {
		std::function<U(T)> f;
		E e;
	public:
		apply_()
		{ }
		apply_(F f, E e)
			: f(f), e(e)
		{ }

		operator bool() const
		{
			return e;
		}
		U operator*() const
		{
			return f(*e);
		}
		apply_& operator++()
		{
			++e;

			return *this;
		}
		apply_ operator++(int)
		{
			apply_ a(*this);

			operator++();

			return a;
		}
	};
	template<class F, class E, class T = typename std::iterator_traits<E>::value_type>
	inline auto apply(F f, E e)
	{
		return apply_<F,E,T>(f, e);
	}
	// f[0], f[1], ...
	template<class F>
	inline auto apply(F f)
	{
		return apply(f, iota<size_t>());
	}


} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_apply()
{
	int a[] = {0,1,2};
	auto b = apply([](int e) { return e*e; }, a);
	decltype(b) c;
	c = b;
	assert (*b == 0);
	assert (*++b == 1);
	b++;
	assert (*b == 4);

	assert (*c == 0);
	assert (*++c == 1);
	c++;
	assert (*c == 4);

	auto d = apply([](int n) { return 1 + n + n*n; });
	assert (*d == 1);
	assert (*++d == 3);
	++d;
	assert (*d == 7);
	
/*	{ // not working with VC 2013
		double a[] = {0,1,2};
		auto e = apply(exp, a);
		assert (*e++ == exp(0));
		assert (*e++ == exp(1));
		assert (*e++ == exp(2));
	}
*/
}

#endif // _DEBUG