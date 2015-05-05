// range_running.h - apply binop to successive elements
#pragma once
#include "range.h"
#include "range_sequence.h"

namespace range {

	template<class I, class O,
		class T = typename std::iterator_traits<I>::value_type>
	class running : public iterator<I> {
		O o;
		iterator<I> i;
		T t;
	public:
		running(I i, O o, T t = T(0))
			: i(i), o(o), t(o(*i,t))
		{ }
		~running()
		{ }

		const T& operator*() const
		{
			return t;
		}
		running& operator++()
		{
			t = o(t, *++i);

			return *this;
		}
		running operator++(int)
		{
			running i_(*this);

			operator++();

			return i_;
		}
	};
	template<class I, class O, class T = typename std::iterator_traits<I>::value_type>
	inline running<I,O> make_running(I i, O o = std::plus<T>(), T t = T(0))
	{
		return running<I,O,T>(i, o, t);
	}

	template<class T>
	inline running<sequence<T>,std::multiplies<T>,T> factorial()
	{
		return make_running(sequence<T>(T(1)), std::multiplies<T>(), T(1));
	};

#ifdef _DEBUG

	inline void test_running()
	{
		int a[] = {1,2,3};
		auto r = make_running(a, std::plus<int>());
		assert (*r == 1);
		++r;
		assert (*r++ == 3);
		assert (*r == 6);

		auto f = factorial<int>();
		assert (*f == 1);
		assert (*++f == 2);
		assert (*++f == 6);
		assert (*++f == 24);
		assert (*++f == 120);
		assert (*++f == 720);
	}

#endif // _DEBUG
} // range
