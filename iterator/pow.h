// pow.h - powers of a number
#pragma once
#include "input.h"

namespace iter {

	template<class T>
	class pow : public input_base<T*, T> {
		T t, t_;
	public:
		pow(T t = 0)
			: t(t), t_(1)
		{ }
		pow(const pow&) = default;
		pow& operator=(const pow&) = default;
		pow(pow&&) = default;
		pow& operator=(pow&&) = default;
		~pow()
		{ }

		T operator*() const
		{
			return t_;
		}
		pow& operator++()
		{
			t_ *= t;

			return *this;
		}
		pow operator++(int)
		{
			pow p(*this);

			operator++();

			return p;
		}
	};

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_pow()
{
	iter::pow<int> p(2);

	assert (*p == 1);
	assert (*++p == 2);
	p++;
	assert (*p == 4);
	assert (*++p == 8);
}

#endif // _DEBUG