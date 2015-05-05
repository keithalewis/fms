// range_pair.h - combine two ranges
#pragma once
#include "range.h"

namespace range {
	// times and values
	template<class I, class J>
	class pair {
		typedef typename std::iterator_traits<I>::value_type T;
		typedef typename std::iterator_traits<J>::value_type U;
		I i;
		J j;
	public:
		pair()
		{ }
		pair(I i, J j)
			: i(i), j(j)
		{ }
		pair(const pair&) = default;
		pair& operator=(const pair&) = default;
		~pair()
		{ }

		bool operator==(const pair& k) const
		{
			return i == k.i && j == k.j;
		}
		std::pair<T,U> operator*() const
		{
			return std::pair<T,U>(*i, *j);
		}
		pair& operator++()
		{
			++i;
			++j;

			return *this;
		}
		pair operator++(int)
		{
			pair k(*this);

			++i;
			++j;

			return k;
		}
	};
	template<class I, class J>
	inline pair<I,J> make_pair(I i, J j)
	{
		return pair<I,J>(i, j);
	}
#ifdef _DEBUG

	inline void test_pair()
	{
		int a[] = {0,1,2};
		{
			auto zi = make_pair(a, a);
			assert (zi == zi);
			int i = 0;
			assert (std::make_pair(a[i],a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]) == *++zi);
		}
		{
			auto zi = range::make_pair(a,
					make_apply([](int i) { return i*i;}, a));
			int i = 0;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *++zi);
		}
	}

#endif // _DEBUG
} // range
