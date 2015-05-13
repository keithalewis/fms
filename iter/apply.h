// apply.h - apply a function to an iter
#pragma once
#include <functional>
#include "enumerator.h"
#include "iota.h"

namespace iter {

	template<class F, class I, class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>>
	class apply_ : public enumerator_base<I,U> {
		std::function<U(T)> f;
		I i;
	public:
		apply_()
		{ }
		apply_(F f, I i)
			: f(f), i(i)
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
	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto apply(F f, I i)
	{
		return apply_<F,I,T>(f, i);
	}
	template<class F>
	inline auto apply(F f, size_t n = 0)
	{
		return apply(f, iota<size_t>(n));
	}


} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_apply()
{
	int a[] = {0,1,2};
	auto b = apply([](int i) { return i*i; }, a);
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
}

#endif // _DEBUG