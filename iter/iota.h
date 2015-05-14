// iota.h - input iterator 0, 1, 2, ...
#pragma once
#include "enumerator.h"

namespace iter {

	// t, t + 1, ...
	template<class T = double>
	class iota_ : public enumerator_base<T*, T> {
		T t;
	public:
		iota_(T t = 0)
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
		iota_& operator++()
		{
			++t;

			return *this;
		}
		iota_ operator++(int)
		{
			iota_ i_(*this);

			operator++();

			return i_;
		}
	};
	template<class T = double>
	inline auto iota(const T& t = T(0))
	{
		return iota_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

using iter::iota_;

inline void test_iota()
{
	iota_<int> i;

	assert (*i == 0);
	assert (*++i == 1);
	i++;
	assert (*i == 2);
}

#endif // _DEBUG