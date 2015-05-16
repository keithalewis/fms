// pair.h - pair of iterators
#pragma once
#include <utility>
#include "enumerator.h"

namespace iter {

	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type>
	class pair_ : public enumerator_base<std::pair<I,J>, std::pair<T,U>,typename std::common_type_t<
			typename std::iterator_traits<I>::iterator_category,
			typename std::iterator_traits<J>::iterator_category>> {
		std::pair<I,J> ij;
	public:
		pair_()
		{ }
		pair_(I i, J j)
			: ij(std::make_pair(i,j))
		{ }
		pair_(const std::pair<I,J>& ij)
			: ij(ij)
		{ }

		operator bool() const
		{
			return ij.first && ij.second;
		}
		std::pair<T,U> operator*() const
		{
			return std::make_pair(*ij.first, *ij.second);
		}
		pair_& operator++()
		{
			++ij.first;
			++ij.second;

			return *this;
		}
		pair_ operator++(int)
		{
			pair_ i_(*this);

			operator++();

			return i_;
		}
	};
	template<class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type>
	inline pair_<I,J,T,U> pair(I i, J j)
	{
		return pair_<I,J,T,U>(i, j);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_pair()
{
	int a[] = {0,1,2};
	int b[] = {2,4,5};

	auto c = pair(std::begin(a),std::begin(b));
	ensure (*c == std::make_pair(0,2));
	c = pair(a,b);
	ensure (*c == std::make_pair(0,2));
	c = pair(a,&b[0]);
	ensure (*c == std::make_pair(0,2));

	ensure (*++c == std::make_pair(1,4));
	c++;
	ensure (*c == std::make_pair(2,5));

	c = pair(a,b);
	pair_<int*,int*> d(a,b);
//	ensure (c == d);
	++c;
//	ensure (c != d);
	d = c;
//	ensure (c == d);
}

#endif // _DEBUG