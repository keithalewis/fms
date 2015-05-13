// choose.h - combinations
#pragma once
#include "enumerator.h"

namespace iter {

	template<class T = double>
	class choose_ : public enumerator_base<T*,T> {
		T n, k, nk;
	public:
		choose_(T n = 0)
			: n(n), k(0), nk(1)
		{ }
		~choose_()
		{ }

		operator T*() const
		{
			 return nullptr;
		}
		operator bool() const
		{
			return k <= n;
		}
		T operator*() const
		{
			return nk;
		}
		choose_& operator++()
		{
			++k;
			nk *= (n - k + 1);
			nk /= k;

			return *this;
		}
		choose_ operator++(int)
		{
			choose_ c(*this);

			operator++();

			return c;
		}
	};
	template<class T = double>
	inline auto choose(const T& t)
	{
		return choose_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include <cassert>
#include "accumulate.h"

using namespace iter;

inline void test_choose()
{
	choose_<> c(4);

	assert (*c == 1);
	assert (*++c == 4);
	c++;
	assert (*c == 6);
	assert (*++c == 4);
	assert (*++c == 1);
	assert (!++c);

	assert (back(sum(choose(4))) == 2*2*2*2);
}

#endif // _DEBUG