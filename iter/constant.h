// constant.h - constant input iterator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T = double>
	class constant_ : public enumerator<void,T,std::input_iterator_tag> {
		T t;
	public:
		// defaults so infinite
		constant_(const T& t = 0)
			: t(t)
		{ }

		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return t;
		}
		constant_& operator++()
		{
			return *this;
		}
		constant_ operator++(int)
		{
			return *this;
		}
	};
	template<class T>
	inline constant_<T> constant(const T& t)
	{
		return constant_<T>(t);
	}
	// shorthand
	template<class T>
	inline constant_<T> c(const T& t)
	{
		return constant_<T>(t);
	}
} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_constant()
{
/*	int a[] = {1};
	auto b = e(a);
	// 32-bit!!!
	ensure (4 == sizeof(a));
	ensure (4 == sizeof(b));
	auto d = c(1);
	ensure (4 == sizeof(d)); // <- zero overhead
*/
	constant_<int> zero;
	ensure (*zero == 0);
	ensure (*++zero == 0);
	ensure (*zero++ == 0);

	constant_<int> two(2);
	ensure (*two == 2);
	ensure (*++two == 2);
	ensure (*two++ == 2);

	auto four = c(4);
	ensure (*four++ == 4 && *++four == 4);
}

#endif // _DEBUG