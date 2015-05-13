// apply.h - apply a function to an iter
#pragma once
#include <functional>
#include "enumerator.h"

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

		operator I() const
		{
			return i;
		}
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
	inline apply_<F,I,T> apply(F f, I i)
	{
		return apply_<F,I,T>(f, i);
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
}

#endif // _DEBUG