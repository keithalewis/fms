// concatenate.h - concatenate an enumerator and an iterator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class I, class J,
		class V = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type>>
	class concatenate_ : public enumerator_base<std::pair<I,J>, V, std::input_iterator_tag> { // <-- lcd category!!!
		std::pair<I,J> ij;
	public:
		concatenate_()
		{ }
		concatenate_(I i, J j)
			: ij(std::make_pair(i,j))
		{ }

		operator bool() const
		{
			return ij.first || ij.second;
		}
		V operator*() const
		{
			return ij.first ? *ij.first : *ij.second;
		}
		concatenate_& operator++()
		{
			if (ij.first)
				++ij.first;
			else
				++ij.second;

			return *this;
		}
		concatenate_ operator++(int)
		{
			concatenate_ k(*this);

			operator++();

			return k;
		}
	};
	template<class I, class J,
		class V = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type>>
	inline concatenate_<I,J,V> concatenate(I i, J j)
	{
		return concatenate_<I,J,V>(i, j);
	}

} // iter

/*
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class V = typename std::iterator_traits<J>::value_type,
	class TU = typename std::common_type_t<T,V>>
inline iter::concatenate_<I,J,TU> operator,(I i, J j)
{
	return iter::concatenate_<I,J,TU>(i, j);
}
*/

#ifdef _DEBUG
#include <cassert>
#include "enumerator/null.h"

using namespace iter;

inline void test_concatenate()
{
	int i[] = {1,2,0};
	int j[] = {3,4};

	{
		concatenate_<null_enumerator<int*>,counted_enumerator<int*>> c(make_null_enumerator(i), make_counted_enumerator(j, 2)), d;
		d = c;
		assert (*d == *c);
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
	{
		auto c = concatenate(make_null_enumerator(i), make_counted_enumerator(j, 2));
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
	{
		auto b = make_null_enumerator(i);
//		auto bb = operator,(b,b);

	}
}

#endif // _DEBUG