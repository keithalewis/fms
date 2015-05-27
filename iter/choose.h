// choose.h - combinations
#pragma once
#include "enumerator.h"

namespace iter {

	// combinatorial choose
	// c(n,0), c(n,1), ...
	template<class T = double>
	class choose_ : public enumerator<void,T,std::input_iterator_tag> {
		T n, k, nk;
	public:
		choose_(T n = 0)
			: n(n), k(0), nk(1)
		{ }
		~choose_()
		{ }

		explicit operator bool() const
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
			nk *= (n - k + 1); // works for ints
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
	template<class T>
	inline auto choose(const T& t)
	{
		return choose_<T>(t);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_choose()
{
	auto c = iter::choose(4);
	auto d(c);
	c = d;

	ensure (*c == 1);
	ensure (*++c == 4);
	c++;
	ensure (*c == 6);
	ensure (*++c == 4);
	ensure (*++c == 1);
	ensure (!++c);
}

#endif // _DEBUG