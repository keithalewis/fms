// range_apply.h - apply a function to a range iterator
#pragma once
#include "range.h"

namespace range {
	// apply function to iterator values
	template<class F, class I,
		class T = typename std::result_of<F(const typename std::iterator_traits<I>::value_type&)>::type>
	class apply : public iterator<T*> {
		F f;
		I i;
	public:
		apply()
		{ }
		apply(F f, I i)
			: f(f), i(i)
		{ }
		apply(const apply&) = default;
		apply& operator=(const apply&) = default;
		~apply()
		{ }

		bool operator==(const apply& i) const
		{
			return false; // i == i.i && f == i.f; // always false !!!
		}
		T operator*() const 
		{
			return f(*i);
		}
		apply& operator++()
		{
			++i;

			return *this;
		}
	};
	template<class F, class I>
	inline apply<F,I> make_apply(F f, I i)
	{
		return apply<F,I>(f, i);
	}
#ifdef _DEBUG

	inline void test_apply()
	{
		int a[] = {0,1,2};
		{
			auto a2 = make_apply([](int i) { return i*i; }, a);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
		{
			auto a1 = make_iterator(&a[0]);
			auto sq = [](int i) { return i*i; };
			auto a2 = make_apply(sq, a1);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
		{
			auto a1 = make_iterator(&a[0]);
			auto sq = [](int i) -> double { return i*i; };
			auto a2 = make_apply(sq, a1);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
		{
			double a[] = {1.1,2.2,3.3};
			auto a1 = make_iterator(&a[0]);
			auto sq = [](double i) -> int { return static_cast<int>(i*i); };
			auto a2 = make_apply(sq, a1);
			assert (*a2 == 1);
			++a2;
			assert (*a2 == 4);
			assert (*++a2 == 10);
		}
		{
			double a[] = {1.1,2.2,3.3};
			auto a1 = make_enumerator(&a[0]);
			auto sq = [](double i) -> int { return static_cast<int>(i*i); };
			auto a2 = make_apply(sq, a1);
			assert (*a2 == 1);
			++a2;
			assert (*a2 == 4);
			assert (*++a2 == 10);
		}
	}

#endif // _DEBUG
} // range
