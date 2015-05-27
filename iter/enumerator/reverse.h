// reverse.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// reverse enumerator
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class reverse_enumerator : public enumerator<std::reverse_iterator<I>,T,C> {
	public:
		using enumerator<std::reverse_iterator<I>>::i;

		reverse_enumerator()
		{ }
		reverse_enumerator(I i)
			: enumerator<std::reverse_iterator<I>,T,C>(std::reverse_iterator<I>(i)) // just like reverse iterators
		{ }

		bool operator==(const reverse_enumerator& j) const
		{
			return i == j.i;
		}
		bool operator!=(const reverse_enumerator& j) const
		{
			return i != j.i;
		}
		std::reverse_iterator<I> iterator()
		{
			return i;
		}

/*		explicit operator bool() const
		{
			return true;
		}

		T operator*() const
		{
			return *i;
		}
		reverse_enumerator& operator++()
		{
			++i;

			return *this;
		}
		reverse_enumerator operator++(int)
		{
			reverse_enumerator r(*this);

			operator++();

			return r;
		}
*/	};
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto make_renumerator(I i)
	{
		return reverse_enumerator<I,T,C>(i);
	}
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto re(I i)
	{
		return reverse_enumerator<I,T,C>(i);
	}
//	template<class T>
//	inline auto re(T*

} // iter


#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_reverse()
{
	int a[] = {1,2,3};
	auto ra = re(a + 3);
	auto rb(ra);
	ra = rb;
	ensure (ra == rb);
	ensure (*ra == 3);
	ensure (*++ra == 2);
	ra++;
	ensure (*ra == 1);
}

#endif // _DEBUG