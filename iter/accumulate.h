// accumulate.h - std::accumulate for enumerations
// accumulate, sum = accumulate<plus>, prod = accumulate<multiplies>
#pragma once
#include <algorithm>
#include <iterator>
#include "enumerator/counted.h"

namespace iter {

	// o(t,e[0]), o(o(t,e[0]), e[1]), ...
	template<class O, class E, class T = typename std::iterator_traits<E>::value_type>
	class accumulate_ : public enumerator_base<E,T> {
		std::function<T(const T&,const T&)> o; E e; T t;
	public:
		accumulate_()
		{ }
		accumulate_(O o, E e, T t)
			: o(o), e(e), t(e ? o(t,*e) : t)
		{ }

		operator bool() const
		{
			return e;
		}
		T operator*() const
		{
			return t;
		}
		accumulate_& operator++()
		{
			if (e)
				t = o(t, *++e);

			return *this;
		}
		accumulate_ operator++(int)
		{
			accumulate_ a(*this);

			operator++();

			return a;
		}
	};
	template<class O, class E, class T = typename std::iterator_traits<E>::value_type>
	inline accumulate_<O,E,T> accumulate(O o, E e, T t)
	{
		return accumulate_<O,E,T>(o, e, t);
	}

	// running sum of enumerator values
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline accumulate_<std::plus<T>,E,T> sum(E e, T t = T(0))
	{
		return accumulate_<std::plus<T>,E,T>(std::plus<T>{}, e, t);
	}

	// running product of  enumerator values
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline accumulate_<std::multiplies<T>,E,T> prod(E e, T t = T(1))
	{
		return accumulate_<std::multiplies<T>,E,T>(std::multiplies<T>{}, e, t);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_accumulate()
{
	int a[] = {1,2,3};
	auto b = accumulate(std::plus<int>{}, e(a,3), 0);
	auto c(b);
	b = c;
	ensure (*b++ == 1);
	ensure (*b == 3);
	ensure (*++b == 6);
	ensure (!++b);
}

#endif // _DEBUG