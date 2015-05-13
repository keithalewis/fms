// pow.h - powers of a number
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T>
	class pow_ : public enumerator_base<T*, T> {
		T t, t_;
	public:
		pow_(T t = 0)
			: t(t), t_(1)
		{ }

		operator T*() const
		{
			return &t_;
		}
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return t_;
		}
		pow_& operator++()
		{
			t_ *= t;

			return *this;
		}
		pow_ operator++(int)
		{
			pow_ p(*this);

			operator++();

			return p;
		}
	};
	template<class T>
	inline auto pow(const T& t)
	{
		return pow_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_pow()
{
	iter::pow_<int> p(2);

	assert (*p == 1);
	assert (*++p == 2);
	p++;
	assert (*p == 4);
	assert (*++p == 8);
}

#endif // _DEBUG