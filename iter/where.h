// where.h - Filter based on a predicate
#pragma once
#include "enumerator.h"
#include "until.h"

namespace iter {

	template<class P, class I, class T = typename std::iterator_traits<I>::value_type>
	class where_ : public enumerator_base<I,T> {
		std::function<bool(const I&)> p;
		I i;
	public:
		where_()
		{ }
		where_(P p, I i)
			: p(p), i(until(p,i))
		{ }

		operator bool() const
		{
			return i;
		}
		T operator*() const
		{
			return *i;
		}
		where_& operator++()
		{
			i = until(p, ++i);

			return *this;
		}
		where_ operator++(int)
		{
			where_ w(*this);

			operator++();

			return w;
		}
	};
	template<class P, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto where(P p, I i)
	{
		return where_<P,I,T>(p, i);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_where()
{
	int a[] = {0,1,2,3,4,5};
	auto b = where([](const int* pi) { return (*pi % 2) != 0; }, a);
	assert (*b == 1);
	assert (*++b == 3);
	b++;
	assert (*b == 5);

	auto c(b);
	b = c;
}

#endif // _DEBUG