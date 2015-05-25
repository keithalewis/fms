// end.h - enumerator with end sentinel
#pragma once
#include "../enumerator.h"

namespace iter {

	// end sentinel enumerator
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class end_enumerator : public enumerator<I,T,C> {
		J e;
	public:
		using enumerator<I,T,C>::i;

		end_enumerator()
		{ }
		end_enumerator(I i, J e)
			: enumerator<I,T,C>(i), e(e)
		{ }

		bool operator==(const end_enumerator& j) const
		{
			return i == j.i && e == j.e;
		}
		bool operator!=(const end_enumerator& j) const
		{
			return i != j.i || e != j.e;
		}
/*		operator I() const
		{
			return i;
		}
		I& iterator()
		{
			return i;
		}
*/
		operator bool() const
		{
			return i != e;
		}
/*		T operator*() const
		{
			return *i;
		}
		end_enumerator& operator++()
		{
			++i;

			return *this;
		}
		end_enumerator operator++(int)
		{
			end_enumerator e(*this);

			operator++();

			return e;
		}
*/	};
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto make_end_enumerator(I i, J e)
	{
		return end_enumerator<I,J,T,C>(i, e);
	}
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto ee(I i, J e)
	{
		return end_enumerator<I,J,T,C>(i, e);
	}
	template<class C,
		class I = typename C::iterator,
		class T = typename C::value_type,
		class IC = typename C::iterator::iterator_category
	>
	inline auto ee(C c)
	{
		return end_enumerator<I,I,T,IC>(std::begin(c), std::end(c));
	}

} // iter


#ifdef _DEBUG
#include <vector>
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_end()
{
	int a[] = {1,2,0};

	{
		auto f = ee(std::begin(a), std::end(a));
		ensure (f);
		ensure (*++f == 2);
		f++;
		ensure (*f++ == 0);
		ensure (!f);
	}
	{
//		std::vector<int> a = {1,2,3};
//		auto b = ee(a);
	}
}

#endif // _DEBUG