// concatenate.h - concatenate an enumerator and an iterator
#pragma once
#include "enumerator.h"

namespace iterator {

	template<class I, class J,
		class U = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type>>
	class concatenate : public enumerator_base<std::pair<I,J>, U> {
		std::pair<I,J> ij;
	public:
		concatenate()
		{ }
		concatenate(I i, J j)
			: ij(std::make_pair(i,j))
		{ }
		concatenate(const concatenate&) = default;
		concatenate& operator=(const concatenate&) = default;
		concatenate(concatenate&&) = default;
		concatenate& operator=(concatenate&&) = default;
		~concatenate()
		{ }

		operator bool() const
		{
			return ij.first || ij.second;
		}
		U operator*() const
		{
			return ij.first ? *ij.first : *ij.second;
		}
		concatenate& operator++()
		{
			if (ij.first)
				++ij.first;
			else
				++ij.second;

			return *this;
		}
		concatenate operator++(int)
		{
			concatenate k(*this);

			operator++();

			return k;
		}
	};
	template<class I, class J,
		class U = typename std::common_type_t<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type>>
	inline concatenate<I,J,U> make_concatenate(I i, J j)
	{
		return concatenate<I,J,U>(i, j);
	}

} // iterator
#ifdef _DEBUG
#include <cassert>

using namespace iterator;

inline void test_concatenate()
{
	int i[] = {1,2,0};
	int j[] = {3,4};

	{
		concatenate<null_enumerator<int*>,counted_enumerator<int*>> c(make_null_enumerator(i), make_counted_enumerator(j, 2)), d;
		d = c;
		assert (*d == *c);
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
	{
		auto c = make_concatenate(make_null_enumerator(i), make_counted_enumerator(j, 2));
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}

}

#endif // _DEBUG