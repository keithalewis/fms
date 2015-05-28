// iota.h - input iterator 0, 1, 2, ...
#pragma once
#include "enumerator.h"

namespace iter {

	// t, t + 1, ...
	template<class T>
	class iota_ : public enumerator_<void, T, std::input_iterator_tag> {
		T t;
	public:
		iota_(T t = 0)
			: t(t)
		{ }

		explicit operator bool() const
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
	template<class T>
	inline auto iota(T t = T(0))
	{
		return iota_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using iter::iota_;

inline void test_iota()
{
	iota_<int> i;

	ensure (*i == 0);
	ensure (*++i == 1);
	i++;
	ensure (*i == 2);

	i = iota(2);
	ensure (*i++ == 2);
	ensure (*i == 3);
	ensure (*++i == 4);
}

#endif // _DEBUG