// reverse.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// reverse enumerator if I is bidirectional or random access
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class reverse_enumerator_ : public enumerator_<std::reverse_iterator<I>,T> {
	public:
		using enumerator_<std::reverse_iterator<I>>::i;

		reverse_enumerator_()
		{ }
		reverse_enumerator_(I i)
			: enumerator_<std::reverse_iterator<I>,T>(std::reverse_iterator<I>(i))
		{ }

		bool operator==(const reverse_enumerator_& j) const
		{
			return i == j.i;
		}
		bool operator!=(const reverse_enumerator_& j) const
		{
			return i != j.i;
		}

		std::reverse_iterator<I> iterator()
		{
			return i;
		}
/*
		explicit operator bool() const
		{
			return i.operator bool();
		}
*/
		T operator*() const
		{
			return *i;
		}
		reverse_enumerator_& operator++()
		{
			++i;

			return *this;
		}
		reverse_enumerator_ operator++(int)
		{
			reverse_enumerator_ r(*this);

			operator++();

			return r;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto reverse_enumerator(I i)
	{
		return reverse_enumerator_<I,T>(i);
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto re(I i)
	{
		return reverse_enumerator(i);
	}

} // iter


#ifdef _DEBUG
#include "include/ensure.h"
#include "counted.h"

using namespace iter;

inline void test_enumerator_reverse()
{
	int a[] = {1,2,3};
	{
		auto ra = re(a + 3);
		auto rb(ra);
		ra = rb;
		ensure (ra == rb);
		ensure (*ra == 3);
		ensure (*++ra == 2);
		ra++;
		ensure (*ra == 1);
	}
	{
		auto b = ce(re(a + 3),3);
		auto c(b);
		b = c;
		ensure (*b == 3);
		ensure (*++b == 2);
		b++;
		ensure (*b == 1);
		ensure (!++b);
	}
}

#endif // _DEBUG