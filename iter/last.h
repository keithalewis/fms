// last.h - last item in an enumeration
// last, back = *last
#pragma once
#include <utility>
#include "enumerator/counted.h"
#include "enumerator/reverse.h"

namespace iter {

	template<class E>
	inline size_t size(E e)
	{
		size_t n = 0;

		while (e) {
			++n;
			--e;
		}

		return n;
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto size(counted_enumerator<I,T> e)
	{
		return e.size();
	}

	/// iterate to just before end
	template<class E>
	inline E last(E e)
	{
		E l(e);

		while (++e) {
			l = e;
		}

		return l;
	}

	template<class E>
	inline E end(E e)
	{
		while (++e)
			;

		return e;
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto end(counted_enumerator<I,T> e)
	{
		return e.end();
	}
	// counted reverse enumerator
	template<class R>
	inline auto rend(R r)
	{
		return ce(re(r.end()),r.size());
	}
	template<class E>
	inline typename std::iterator_traits<E>::value_type back(E e)
	{
		return *last(e);
	}
	// sum null enumerators
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline T sum0(E e, T s = T(0))
	{
		while (e) {
			s += *e;
			++e;
		}

		return s;
	}
	// multiply null enumerators
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline T prod1(E e, T s = T(1))
	{
		while (e) {
			s *= *e;
			++e;
		}

		return s;
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_last() {
	int a[] = {0,1,2};

	auto b = ce(a);
	ensure (b.size() == 3);
	ensure (size(b) == 3);

	ensure (*iter::last(b) == 2);
	auto ea = iter::end(b);
	ensure (ea[-1] == 2);

	auto ra = iter::rend(b);
	ensure (ra && *ra == 2);
	++ra;
	ensure (ra && *ra == 1);
	ra++;
	ensure (ra && *ra == 0);
	ra++;
	ensure (!ra);

}

#endif // _DEBUG