// where.h - Filter based on a predicate
#pragma once
#include "enumerator.h"
#include "until.h"

namespace iter {

	template<class P, class I, class T = typename std::iterator_traits<I>::value_type>
	class where_ : public enumerator_<I,T,std::input_iterator_tag> {
		P p;
	public:
		using enumerator_<I,T,std::input_iterator_tag>::i;

		where_()
		{ }
		where_(P p, I i)
			: enumerator_<I,T,std::input_iterator_tag>(until(p,i)), p(p)
		{ }

		explicit operator bool() const
		{
			return i;
		}
		T operator*() const
		{
			return *i;
		}
		where_& operator++()
		{
			i = until(p, ++i);

			return *this;
		}
		where_ operator++(int)
		{
			where_ w(*this);

			operator++();

			return w;
		}
	};
	template<class P, class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto where(P p, I i)
	{
		return where_<P,I,T>(p, i);
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_where()
{
	int a[] = {0,1,2,3,4,5};
	// ambiguous with MSVC
//	auto b = where(+[](const int* pi) { return (*pi % 2) != 0; }, a);
	auto b = where(std::function<bool(const int*)>([](const int* pi) { return (*pi % 2) != 0; }), a);
	auto c(b);
	b = c;
	ensure (*b == 1);
	ensure (*++b == 3);
	b++;
	ensure (*b == 5);
}

#endif // _DEBUG