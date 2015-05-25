// zigg.h - monotonically climb through iterators
#pragma once
#include "enumerator.h"

namespace iter {

	// e0[0], e0[1],...,e1[0] when *e0 > e1[0], ...
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	class zigg_ : public enumerator<I,T,std::input_iterator_tag> {
		typename std::iterator_traits<I>::value_type i_, _i; // current and next iter
		size_t n;
	public:
		using enumerator<I,T,std::input_iterator_tag>::i;

		zigg_()
		{ }
		zigg_(I i)
			: enumerator<I,T,std::input_iterator_tag>(i), i_(*i), _i(*++i), n(0)
		{ }

		// current enumerator index
		size_t at() const
		{
			return n;
		}

		operator bool() const
		{
			return i_;
		}
		T operator*()
		{
			return *i_;
		}
		zigg_& operator++()
		{
			++i_;

			if (!i_) {
				i_ = *i; // i has already been incremented
				++i;
				if (i)
					_i = *i;
			}
			else if (*i_ > *_i) {
				i_ = _i;
				++i;
				if (i)
					_i = *i;
			}

			return *this;
		}
		zigg_ operator++(int)
		{
			zigg_ z(*this);

			operator++();

			return z;
		}
	};
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	inline auto zigg(I i)
	{
		return zigg_<I,T>(i);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "fmap.h"
#include "iota.h"

using namespace iter;

inline void test_zigg()
{
/*	int a[2][3] = {
		{1,3,5},
		{0,4,8}
	};
	// => 1,4,8
	auto aa = concatenate(unit(e(a[0])),unit(e(a[1])));
	auto b = *aa;
	ensure (*b == 1);
	ensure (*++b == 3);
	ensure (*++b == 5);
	aa++;
	b = *aa;
	ensure (*b == 0);
	ensure (*++b == 4);
	ensure (*++b == 8);

	aa = concatenate(unit(e(a[0])),unit(e(a[1])));
	auto z = zigg(aa);
	ensure (*z == 1);
	ensure (*++z == 4);
	ensure (*++z == 8);
	*/
}

#endif // _DEBUG