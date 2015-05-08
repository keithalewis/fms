// concatenate.h - concatenate an enumerator and an iterator
#pragma once
#include "enumerator.h"

namespace iterator {

	template<class I, class J,
		class T = typename std::common_type<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>::type>
	class concatenate : public enumerator<J, T> {
		I i;
		J j;
	public:
		concatenate()
		{ }
		concatenate(I i, J j)
			: i(i), j(j)
		{ }
		concatenate(const concatenate&) = default;
		concatenate& operator=(const concatenate&) = default;
		concatenate(concatenate&&) = default;
		concatenate& operator=(concatenate&&) = default;
		~concatenate()
		{ }

		T operator*() const
		{
			return i ? *i : *j;
		}
		concatenate& operator++()
		{
			i ? ++i : ++j;

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
		class T = typename std::common_type<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>::type>
	inline concatenate<I,J,T> make_concatenate(I i, J j)
	{
		return concatenate<I,J,T>(i, j);
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
		concatenate<enumerator<const int*>,enumerator<const int*>> c(make_enumerator(i), make_enumerator(j)), d;
		d = c;
		assert (*d == *c);
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
	{
		auto c = make_concatenate(make_enumerator(i), make_enumerator(j));
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
	{
		auto c = make_concatenate(make_enumerator(i), make_enumerator(j));
		assert (*c == 1);
		assert (*++c == 2);
		assert (*++c == 3);
		c++;
		assert (*c == 4);
	}
}

#endif // _DEBUG