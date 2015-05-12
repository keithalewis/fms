// pair.h - pair of iterators
#pragma once
#include <utility>
#include "input.h"

namespace iter {

	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type>
	class pair : public input_base<std::pair<I,J>, std::pair<T,U>> {
		std::pair<I,J> ij;
	public:
		pair()
		{ }
		pair(I i, J j)
			: ij(std::make_pair(i,j))
		{ }
		pair(const std::pair<I,J>& ij)
			: ij(ij)
		{ }
/*		pair(const pair&) = default;
		pair(pair&&) = default;
		pair& operator=(const pair&) = default;
		pair& operator=(pair&&) = default;
*/		~pair()
		{ }
/*
		bool operator==(const pair& p) const
		{
			return ij == p.ij;
		}
		bool operator!=(const pair& p) const
		{
			return !operator==(p);
		}
*/		operator std::pair<I,J>()
		{
			return ij;
		}

		std::pair<T,U> operator*() const
		{
			return std::make_pair(*ij.first, *ij.second);
		}
		pair& operator++()
		{
			++ij.first;
			++ij.second;

			return *this;
		}
		pair operator++(int)
		{
			pair i_(*this);

			operator++();

			return i_;
		}
	};
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type>
	inline pair<I,J,T,U> make_pair(I i, J j)
	{
		return pair<I,J,T,U>(i, j);
	}

} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_pair()
{
	int a[] = {0,1,2};
	int b[] = {2,4,5};

	auto c = make_pair(std::begin(a),std::begin(b));
	assert (*c == std::make_pair(0,2));
	c = make_pair(a,b);
	assert (*c == std::make_pair(0,2));
	c = make_pair(a,&b[0]);
	assert (*c == std::make_pair(0,2));

	assert (*++c == std::make_pair(1,4));
	c++;
	assert (*c == std::make_pair(2,5));

	c = make_pair(a,b);
	pair<int*,int*> d(a,b);
//	assert (c == d);
	++c;
//	assert (c != d);
	d = c;
//	assert (c == d);
}

#endif // _DEBUG