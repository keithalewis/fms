// cycle.h - cyclic enumerator
#pragma once
#include "enumerator.h"

namespace iter {

	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class cycle_ : public I {
		I b;
	public:
		cycle_()
		{ }
		cycle_(I i)
			: I(i), b(i)
		{ }

		// same operator bool() const
		// same operator*()
		cycle_& operator++()
		{
			I::operator++();
			if (!I::operator bool())
				I::operator=(b);

			return *this;
		}
		// same operator++(int)
	};
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto cycle(I i)
	{
		return cycle_<I,T,C>(i);
	}

} // iter
#ifdef _DEBUG
#include "include/ensure.h"
#include "enumerator/counted.h"

inline void test_cycle()
{
	int a[] = {0,1};
	auto b = cycle(ce(a));
	ensure (*b == 0);
	ensure (*++b == 1);
	ensure (*++b == 0);
	ensure (*++b == 1);
	ensure (*++b == 0);
}

#endif // _DEBUG