// end.h - enumerator with end sentinel
#pragma once
#include "../enumerator.h"

namespace iter {

	// end sentinel enumerator
	template<class I, class J = I, class T = typename std::iterator_traits<I>::value_type>
	class end_enumerator : public enumerator<I,T> {
		J e;
	public:
		using enumerator<I,T>::i;

		end_enumerator()
		{ }
		end_enumerator(I i, J e)
			: enumerator<I,T>(i), e(e)
		{ }

		operator bool() const
		{
			return i != e;
		}
		T operator*() const
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
	};
	template<class I, class J = I, class T = typename std::iterator_traits<I>::value_type>
	inline end_enumerator<I,J,T> make_end_enumerator(I i, J e)
	{
		return end_enumerator<I,J,T>(i, e);
	}

} // iter


#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_enumerator_end()
{
	int a[] = {1,2,0};

	{
		auto f = make_end_enumerator(std::begin(a), std::end(a));
		assert (f);
		assert (*++f == 2);
		f++;
		assert (*f++ == 0);
		assert (!f);
	}
}

#endif // _DEBUG