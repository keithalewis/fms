// end.h - enumerator with end sentinel
#pragma once
#include "../enumerator.h"

namespace iter {

	// end sentinel enumerator
	template<class I, class J = I, class T = typename std::iterator_traits<I>::value_type>
	class end_enumerator : public enumerator_base<I,T> {
		I i;
		J e;
	public:
		typedef typename enumerator_traits<I>::is_counted is_counted; // for tag dispatch
		end_enumerator()
		{ }
		end_enumerator(I i, J e)
			: i(i), e(e)
		{ }

		bool operator==(const end_enumerator& j) const
		{
			return i == j.i && e == j.e;
		}
		bool operator!=(const end_enumerator& j) const
		{
			return i != j.i || e != j.e;
		}
		operator I() const
		{
			return i;
		}
		I& iterator()
		{
			return i;
		}

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
	template<class I, class J = I, class T = typename std::iterator_traits<I>::value_type>
	inline end_enumerator<I,J,T> ee(I i, J e)
	{
		return end_enumerator<I,J,T>(i, e);
	}

} // iter


#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_end()
{
	int a[] = {1,2,0};

	{
		auto f = make_end_enumerator(std::begin(a), std::end(a));
		ensure (f);
		ensure (*++f == 2);
		f++;
		ensure (*f++ == 0);
		ensure (!f);
	}
}

#endif // _DEBUG