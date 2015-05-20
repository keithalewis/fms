// skip.h - skip elements
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {

	// i[n], i[n+1], ...
	template<class N, class I>
	inline I skipn(N n, I i)
	{
		while (i && n--)
			++i;

		return i;
	}
	// specialize skip for counted_enumerator
	template<class N, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto skipn(N n, counted_enumerator<I,T> e)
	{
		n = std::min<size_t>(n, e.size());
		std::advance(e.iterator(), n);

		return counted_enumerator<I,T>(e.iterator(), e.size() - n);
	}

	// *i[n]
	template<class N, class I>
	inline typename std::iterator_traits<I>::value_type at(N n, I i)
	{
		return *skipn(n, i);
	}

	// i[n[0]], i[n[0] + n[1]], ...
	template<class N, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class skip_ : public enumerator<I,T,C> {
		N n;
	public:
		using enumerator<I,T,C>::i;

		skip_()
		{ }
		skip_(N n, I i)
			: enumerator<I,T,C>(skipn(*n,i)), n(n)
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
			skip_ s(*this);

			operator++();

			return s;
		}
	};
	template<class N, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto skip(N n, I i)
	{
		return skip_<N,I,T,C>(n, i);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_skip() {
	int a[] = {0,1,2};

	ensure (*skipn(2, a) == 2);
	ensure (at(1, a) == 1);

	int b[] = {0,1,2,3,4,5};
	auto c = skip(a, b);
	ensure (*c++ == 0);
	ensure (*c == 1);
	ensure (*++c == 3);

	auto d = ce(b);
	ensure (d.size() == 6);
	ensure (*d == 0);

	d = skipn(1,d);
	ensure (d.size() == 5);
	ensure (*d == 1);

	d = skipn(100,d);
	ensure (d.size() == 0);
}

#endif // _DEBUG