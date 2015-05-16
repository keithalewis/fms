// skip.h - skip elements
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {

	// i[n], i[n+1], ...
	template<class I>
	inline I skipn(size_t n, I i)
	{
		while (i && n--)
			++i;

		return i;
	}

	template<class I>
	inline typename std::iterator_traits<I>::value_type at(size_t n, I i)
	{
		return *skipn(n, i);
	}

	// i[n[0]], i[n[0] + n[1]], ...
	template<class N, class I, 
		class T = typename std::iterator_traits<I>::value_type>
	class skip_ : public enumerator<I,T> {
		N n;
//		I i;
	public:
		using enumerator<I,T>::i;
		skip_()
		{ }
		skip_(N n, I i)
			: enumerator<I,T>(skipn(*n,i)), n(n)
		{ }

		operator bool() const
		{
			return i;
		}
		T operator*() const
		{
			return *i;
		}
		skip_& operator++()
		{
			if (++n)
				i = skipn(*n, i);

			return *this;
		}
		skip_ operator++(int)
		{
			skip_ s_(*this);

			operator++();

			return s_;
		}
	};
	template<class N, class I, 
		class T = typename std::iterator_traits<I>::value_type>
	inline auto skip(N n, I i)
	{
		return skip_<N,I,T>(n, i);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

inline void test_skip() {
	int a[] = {0,1,2};

	assert (*skipn(2, a) == 2);
	assert (at(1, a) == 1);

	int b[] = {0,1,2,3,4,5};
	auto c = skip(a, b);
	assert (*c++ == 0);
	assert (*c == 1);
	assert (*++c == 3);

}

#endif // _DEBUG