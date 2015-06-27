// constant.h - constant input iterator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T = double>
	class constant_ : public enumerator_<void,T,std::input_iterator_tag> {
		T t;
	public:
		constant_(const T& t = 0)
			: t(t)
		{ }

		// defaults to infinite
		explicit operator bool() const
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
	inline auto constant(const T& t)
	{
		return constant_<T>(t);
	}
	// shorthand
	template<class T>
	inline auto c(const T& t)
	{
		return constant(t);
	}
} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_constant()
{
	int a[] = {1};
	static_assert (sizeof(int) == sizeof(a), "time for a new compiler");
	auto b = e(a);
//	static_assert (sizeof(int) == sizeof(b), "time for a new compiler"); // 8 on gcc
	auto d = c(1);
	static_assert (sizeof(int) == sizeof(d), "time for a new compiler"); // <- zero overhead

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