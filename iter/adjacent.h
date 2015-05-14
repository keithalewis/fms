// adjacent.h - apply binary operator to adjacent elements
// adjacent, delta = adjacent<minus>
#pragma once
#include <numeric>
#include "enumerator.h"

namespace iter {

	// e[0] - t, e[1] - e[0], ...
	template<class O, class E, class T = typename std::iterator_traits<E>::value_type>
	class adjacent_ : public enumerator_base<E,T> {
		O o;
		E e;
		T t;
	public:
		adjacent_()
		{ }
		adjacent_(O o, E e, T t)
			: o(o), e(e), t(t)
		{ }

		operator bool() const
		{
			return e;
		}
		T operator*() const
		{
			return *e - t;
		}
		adjacent_& operator++()
		{
			t = *e++;

			return *this;
		}
		adjacent_ operator++(int)
		{
			adjacent_ a(*this);

			operator++();

			return a;
		}
	};
	template<class O, class E, class T = typename std::iterator_traits<E>::value_type>
	inline auto adjacent(O o, E e, T t)
	{
		return adjacent_<O,E,T>(o, e, t);
	}
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline auto delta(E e, T t = T(0))
	{
		return adjacent(std::minus<T>{}, e, t);
	}

} // iter

#ifdef _DEBUG
#include <cassert>
//#include "apply.h"
//#include "expr.h"
//#include "iota.h"

using namespace iter;

inline void test_adjacent()
{
	{
		int a[] = {1,4,9};
		auto b = delta(a);
		auto c(b);
		b = c;
		assert (*b++ == 1);
		assert (*b == 3);
		assert (*++b == 5);
	}
	{
		int a[] = {1,4,9};
		auto b = delta(a, 1);
		auto c(b);
		b = c;
		assert (*b++ == 0);
		assert (*b == 3);
		assert (*++b == 5);
	}
}

#endif // _DEBUG