// timeseries.h - iterator over increasing time values
#pragma once
#ifdef _DEBUG
#include <cassert>
#include <vector>
#endif
#include <functional>
#include <iterator>

namespace timeseries {

	template<class I>
	class forward_iterator : public std::iterator<std::forward_iterator_tag, typename std::iterator_traits<I>::value_type> {
		typedef typename std::iterator_traits<I>::value_type T;
		I i;
	public:
		forward_iterator()
		{ }
		forward_iterator(I i)
			: i(i)
		{ }
		forward_iterator(const forward_iterator&) = default;
		forward_iterator& operator=(const forward_iterator&) = default;
		~forward_iterator()
		{ }

		bool operator==(const forward_iterator& i) const
		{
			return i.operator==(i);
		}
		bool operator!=(const forward_iterator& i) const
		{
			return !i.operator==(i);
		}
		T operator*(void) const
		{
			return *i;
		}
		T& operator*(void)
		{
			return *i;
		}
		forward_iterator& operator++()
		{
			++i;

			return *this;
		}
		forward_iterator operator++(int)
		{
			forward_iterator i_(i);

			++i;

			return i_;
		}
	};
	template<class I>
	inline forward_iterator<I> make_forward_iterator(const I& i)
	{
		return forward_iterator<I>(i);
	}
#ifdef _DEBUG
	inline void test_forward_iterator()
	{
		int a[] = {0,1,2};

		{
			forward_iterator<int*> ia(a);
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
			*ia = 3;
			assert (*ia == 3);
			*ia = 2;
		}
		{
//			auto ia = make_forward_iterator(a); // a -> int[3]
//			auto ia = make_forward_iterator(std::begin(a)); // ok
			auto ia = make_forward_iterator(&a[0]);
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
			*ia = 3;
			assert (*ia == 3);
			*ia = 2;
		}
		{
			std::vector<int> va(std::begin(a), std::end(a));
			auto ia = make_forward_iterator(va.begin());
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
			*ia = 3;
			assert (*ia == 3);
			*ia = 2;
		}
	}

#endif // _DEBUG
	// apply function to iterator values
	template<class F, class IT>
	class apply : public forward_iterator<IT> {
		using T = typename std::iterator_traits<IT>::value_type;
		F f;
		IT it;
	public:
		apply()
		{ }
		apply(F f, IT it)
			: f(f), it(it)
		{ }
		apply(const apply&) = default;
		apply& operator=(const apply&) = default;
		~apply()
		{ }

		bool operator==(const forward_iterator& i) const
		{
			return false; // it == i.it && f == i.f; // always false !!!
		}
		T operator*() const 
		{
			return f(*it);
		}
		apply& operator++()
		{
			++it;

			return *this;
		}
		apply operator++(int)
		{
			apply i(*this);

			++it;

			return i;
		}
	};
	template<class F, class IT>
	inline apply<F,IT> make_apply(F f, IT it)
	{
		return apply<F,IT>(f, it);
	}
/*	template<class IT, class F, class T = typename std::iterator_traits<IT>::value_type>
	inline auto  make_apply(const F& f, IT it) -> apply<IT,typename std::result_of<f(T)>>
	{
		return apply<IT,typename std::result_of<f(T)>>(f, it);
	}
*/
//	template<class T, class U>
//	inline forward_iterator 
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
			auto a1 = make_forward_iterator(&a[0]);
			auto sq = [](int i) { return i*i; };
			auto a2 = make_apply(sq, a1);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
	}

#endif // _DEBUG
	// times and values
	template<class IT, class IU>
	class pair {
		typedef typename std::iterator_traits<IT>::value_type T;
		typedef typename std::iterator_traits<IU>::value_type U;
		IT it;
		IU iu;
	public:
		pair()
		{ }
		pair(IT it, IU iu)
			: it(it), iu(iu)
		{ }
		pair(const pair&) = default;
		pair& operator=(const pair&) = default;
		~pair()
		{ }

		bool operator==(const pair& i) const
		{
			return it == i.it && iu == i.iu;
		}
		std::pair<T,U> operator*() const
		{
			return std::pair<T,U>(*it, *iu);
		}
/*		std::pair<T,U>& operator*()
		{
			return std::pair<T,U>(*it, *iu);
		}
*/		pair& operator++()
		{
			++it;
			++iu;

			return *this;
		}
		pair operator++(int)
		{
			pair i(*this);

			++it;
			++iu;

			return i;
		}
	};
	template<class IT, class IU>
	inline pair<IT,IU> make_pair(IT it, IU iu)
	{
		return pair<IT,IU>(it, iu);
	}
#ifdef _DEBUG

	inline void test_pair()
	{
		int a[] = {0,1,2};
		{
			auto zi = make_pair(a, a);
			assert (zi == zi);
			int i = 0;
			assert (std::make_pair(a[i],a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]) == *++zi);
		}
		{
			auto zi = timeseries::make_pair(a, make_apply([](int i) { return i*i;}, a));
			int i = 0;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *++zi);
		}
	}

#endif // _DEBUG
} // timeseries