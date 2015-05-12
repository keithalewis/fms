// apply.h - apply a function to an iter
#pragma once
#include <functional>
#include "input.h"

namespace iter {

	template<class F, class I, class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>>
	class apply : public input_base<I,U> {
		std::function<U(T)> f;
		I i;
	public:
		apply()
		{ }
		apply(F f, I i)
			: f(f), i(i)
		{ }
/*		apply(const apply&) = default;
		apply(apply&&) = default;
		apply& operator=(const apply&) = default;
		apply& operator=(apply&&) = default;
*/		~apply()
		{ }
/*
		operator I()
		{
			return i;
		}
*/
		operator bool() const
		{
			return i;
		}
		U operator*() const
		{
			return f(*i);
		}
		apply& operator++()
		{
			++i;

			return *this;
		}
		apply operator++(int)
		{
			apply a(*this);

			operator++();

			return a;
		}
	};
	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	inline apply<F,I,T> make_apply(F f, I i)
	{
		return apply<F,I,T>(f, i);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_apply()
{
	int a[] = {0,1,2};
	auto b = make_apply([](int i) { return i*i; }, a);
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
}

#endif // _DEBUG