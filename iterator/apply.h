// apply.h - apply a function to an iterator
#pragma once
#include "input.h"

namespace iterator {

	template<class F, class I, class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>>
	class apply : public input<I,T> {
		std::function<U(T)> f;
	public:
		apply()
		{ }
		apply(F f, I i)
			: f(f), input<I,T>(i)
		{ }
		apply(const apply&) = default;
		apply(apply&&) = default;
		apply& operator=(const apply&) = default;
		apply& operator=(apply&&) = default;
		~apply()
		{ }

		U operator*() const
		{
			return f(*input<I,T>::i);
		}
		apply& operator++()
		{
			input<I,T>::operator++();

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

} // iterator

#ifdef _DEBUG
#include <cassert>

using namespace iterator;

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