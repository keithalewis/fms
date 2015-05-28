// adjacent.h - apply binary operator to adjacent elements
// adjacent, delta = adjacent<minus>
#pragma once
#include <numeric>
#include "enumerator.h"

namespace iter {

	// o(i[0], t), o(i[1], i[0]), ...
	template<class O, class I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	class adjacent_ : public I {
		O o;
		T t;
	public:
		adjacent_()
		{ }
		adjacent_(O o, I i, T t)
			: I(i), o(o), t(t)
		{ }

		explicit operator bool() const
		{
			return I::operator bool();
		}
		T operator*() const
		{
			return o(I::operator*(), t);
		}
		adjacent_& operator++()
		{
			t = I::operator*();
			I::operator++();

			return *this;
		}
		adjacent_ operator++(int)
		{
			adjacent_ a(*this);

			operator++();

			return a;
		}
	};
	template<class O, class I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto adjacent(O o, I i, T t)
	{
		return adjacent_<O,I,T>(o, i, t);
	}
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto delta(I i, T t = T(0))
	{
		return adjacent(std::minus<T>{}, i, t);
	}
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto ratio(I i, T t = T(1))
	{
		return adjacent(std::divides<T>{}, i, t);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
//#include "apply.h"
//#include "expr.h"
//#include "iota.h"

using namespace iter;

inline void test_adjacent()
{
	{
		int a[] = {1,4,9};
		auto b = delta(e(a));
		auto c(b);
		b = c;
		ensure (*b++ == 1);
		ensure (*b == 3);
		ensure (*++b == 5);
	}
	{
		int a[] = {1,4,9};
		auto b = delta(e(a), 1);
		auto c(b);
		b = c;
		ensure (*b++ == 0);
		ensure (*b == 3);
		ensure (*++b == 5);
	}
	{
		int a[] = {1,2,4};
		auto b = ratio(e(a), 1);
		auto c(b);
		b = c;
		ensure (*b++ == 1);
		ensure (*b == 2);
		ensure (*++b == 2);
	}
}

#endif // _DEBUG