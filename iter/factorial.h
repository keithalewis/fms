// factorial.h - factorial enumerator
#pragma once
#include <stdexcept>
#include "accumulate.h"
#include "iota.h"

namespace iter {

	template<class T = double>
	class factorial_ : public enumerator_base<const T*,T> {
		T i, n_; // input index, n!
	public:
		factorial_()
			: i(0), n_(1)
		{
		}

		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return n_;
		}
		factorial_& operator++()
		{
			n_ *= ++i;

			return *this;
		}
		factorial_ operator++(int)
		{
			factorial_ f(*this);

			operator++();

			return f;
		}
	};
	template<class T = double>
	inline auto factorial()
	{
		return factorial_<T>();
	}

} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_factorial()
{
	factorial_<int> f;
	assert (*f++ == 1);
	assert (*f == 1);
	assert (*++f == 2);
	assert (*++f == 6);
	assert (*++f == 24);
	assert (*++f == 120);
	assert (*++f == 720);

	factorial_<int> g(f);
	f = g;
}

#endif // _DEBUG