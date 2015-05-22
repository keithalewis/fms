// fmap.h - enumerator of enumerators
#pragma once
#include <functional>
#include "enumerator.h"

namespace iter {

	// f(i[0]), f(i[1]), ...
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class fmap_ : public enumerator<I,U,C> {
		std::function<U(T)> f;
	public:
		using enumerator<I,U,C>::i;
		typedef typename enumerator_traits<I>::is_counted is_counted;

		fmap_()
		{ }
		fmap_(F f, I i)
			: enumerator<I,U,C>(i), f(f)
		{ }

		operator bool() const
		{
			return i;
		}
		U operator*() const
		{
			return f(*i);
		}
		fmap_& operator++()
		{
			++i;

			return *this;
		}
		fmap_ operator++(int)
		{
			fmap_ f_(*this);

			operator++();

			return f_;
		}
	};
	template<class F, class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::result_of_t<F(T)>,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	inline auto fmap(F f, I i)
	{
		return fmap_<F,I,T,U,C>(f, i);
	}

	// bind
	// return

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include "constant.h"

inline void test_fmap()
{
	{
		int a[] = {0,1,2};
	
		// {{0,1,2},{1,2},{2}}
		auto aa = fmap([&](int i) { return ce(a+i, 3-i); }, a);
		auto b = *aa;
		ensure (*b == 0);
		ensure (*++b == 1);
		b++;
		ensure (*b == 2);

		b = *++aa;
		ensure (*b == 1);
		++b;
		ensure (*b == 2);

		aa++;
		b = *aa;
		ensure (*b == 2);
		ensure (!++b);

	}
}

#endif // _DEBUG