// fmap.h - enumerator of enumerators
#pragma once
#include "enumerator.h"

namespace iter {

	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	class fmap_ : enumerator_base<I, std::result_of_t<F(T)>> {
		F f;
		I i;
	public:
		fmap_()
		{ }
		fmap_(F f, I i)
			: f(f), i(i)
		{ }

		operator bool() const
		{
			return i;
		}
		std::result_of_t<F(T)> operator*()
		{
			return f(*i);
		}
		fmap_& operator++()
		{
			++i;

			return *this;
		}
		fmap_ operator++(int)
		{
			fmap_ f_(*this);

			operator++();

			return f_;
		}
	};
	template<class F, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto fmap(F f, I i)
	{
		return fmap_<F,I,T>(f, i);
	}
/*
	template<class F, class I, class T = std::iterator_traits<I>::value_type>
	class flatten_ : enumerator_base<I,T> {
		const enumerator_base<enumerator_base<I,T>,T>& ii;
	public:
		flatten_()
		{ }
		flatten_(const enumerator_base<enumerator_base<I,T>,T>& ii)
			: ii(ii)
		{ }

		operator bool() const
		{
			return true;
		}

	// bind
	// return
*/
} // iter

#ifdef _DEBUG
#include <cassert>
#include "iota.h"
#include "take.h"

inline void test_fmap()
{
	int a[] = {0,1,2};
	auto aa = fmap([](int i) { return take(i, iota(i)); }, a);
	auto b = *aa;
	assert (!b);
	b = *++aa;
	assert (*b == 1);
	b++;
	assert (!b);
	aa++;
	b = *aa;
	assert (*b == 2);
	assert (*++b == 3);
	assert (!++b);
	assert (aa);
//	assert (!++aa); // oops, a is not counted
}

#endif // _DEBUG