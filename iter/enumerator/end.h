// end.h - enumerator with end sentinel
#pragma once
#include "../enumerator.h"

namespace iter {

	// end sentinel enumerator
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	class end_enumerator_ : public enumerator_<I,T> {
		J e;
	public:
		using enumerator_<I,T>::i;

		end_enumerator_()
		{ }
		end_enumerator_(I i, J e)
			: enumerator_<I,T>(i), e(e)
		{ }

		bool operator==(const end_enumerator_& j) const
		{
			return i == j.i && e == j.e;
		}
		bool operator!=(const end_enumerator_& j) const
		{
			return i != j.i || e != j.e;
		}

		I iterator() const
		{
			return i;
		}
		J end() const
		{
			return e;
		}
		
		explicit operator bool() const
		{
			return i != e;
		}
		end_enumerator_& operator++()
		{
			++i;

			return *this;
		}
		end_enumerator_ operator++(int)
		{
			end_enumerator_ e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto end_enumerator(I i, J e)
	{
		return end_enumerator_<I,J,T>(i, e);
	}
	template<class I, class J = I, 
		class T = typename std::iterator_traits<I>::value_type
	>
	inline auto ee(I i, J e)
	{
		return end_enumerator_<I,J,T>(i, e);
	}
	template<class C,
		class I = typename C::iterator,
		class T = typename C::value_type
	>
	inline auto ee(C& c)
	{
		return end_enumerator_<I,I,T>(std::begin(c), std::end(c));
	}

} // iter


#ifdef _DEBUG
#include <vector>
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_end()
{
	int a[] = {1,2,3};

	{
		auto f = ee(std::begin(a), std::end(a));
		ensure (f);
		ensure (*++f == 2);
		f++;
		ensure (*f++ == 3);
		ensure (!f);
	}
	{
		std::vector<int> a = {1,2,3};
		auto b = ee(a);
		auto c(b);
		b = c;
		ensure (*b == 1);
		ensure (*++b == 2);
		b++;
		ensure (*b == 3);
		ensure (!++b);
	}
}

#endif // _DEBUG