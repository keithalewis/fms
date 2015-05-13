// skip.h
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {

	template<class I>
	inline I skipn(I i, size_t n)
	{
		while (i && n--)
			++i;

		return i;
	}

	template<class I>
	inline typename std::iterator_traits<I>::value_type at(I i, size_t n)
	{
		return *skipn(i, n);
	}

	// i skips by each n
	template<class I, class S, 
		class T = typename std::iterator_traits<I>::value_type>
	class skip_ : public enumerator_base<I,T> {
		I i;
		S s;
	public:
		skip_()
		{ }
		skip_(I i, S s)
			: i(skipn(i,*s)), s(s)
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
			if (++s)
				i = skipn(i, *s);

			return *this;
		}
		skip_ operator++(int)
		{
			skip_ s_(*this);

			operator++();

			return s_;
		}
	};
	template<class I, class S, 
		class T = typename std::iterator_traits<I>::value_type>
	inline auto skip(I i, S s)
	{
		return skip_<I,S,T>(i, s);
	}

} // iter

#ifdef _DEBUG
#include <cassert>
#include "constant.h"
#include "iota.h"
#include "take.h"

inline void test_skip() {
	int a[] = {0,1,2};

	assert (*skipn(a,2) == 2);
	assert (at(a, 1) == 1);

	auto b = skip(take(iota(0), 7), c(2));
	assert (*b == 2);
	assert (*++b == 4);
	b++;
	assert (*b == 6);
	assert (!++b);
	assert (!++b);
	assert (!b++);
}

#endif // _DEBUG