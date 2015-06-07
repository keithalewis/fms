// zigg.h - monotonically climb through iterators
#pragma once
#include "enumerator.h"

namespace iter {

	// e0, e1 = after(*e0, e1), e2 = after(*e1,e2), ...
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type::value_type
	>
	class zigg_ : public enumerator_<I,T,std::input_iterator_tag> {
		typename std::iterator_traits<I>::value_type _i;
	public:
		using enumerator_<I,T,std::input_iterator_tag>::i;

		zigg_()
		{ }
		zigg_(I i)
			: enumerator_<I,T,std::input_iterator_tag>(i), _i(*i)
		{ }

		operator bool() const
		{
			return i && _i;
		}
		T operator*()
		{
			return *_i;
		}
		zigg_& operator++()
		{
			T t = *_i;
			_i = *++i;
			while (_i && *_i < t)
				++_i;

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
	// {5,10,15...},{4,8,12...},{3,6,9...},{2,4,6...},{1,2,3...}
	auto f = [](int i) { return c(5-i)*iota(1); };
	auto a = fmap(f, iota(0));
	auto b = zigg(a);
	ensure(*b == 5);
	++b;
	ensure(*b == 8);
	++b;
	ensure(*b == 9);
	++b;
	ensure(*b == 10);
	++b;
	ensure(*b == 10);
}

#endif // _DEBUG