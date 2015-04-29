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
		forward_iterator& operator++()
		{
			++i;

			return *this;
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
			assert (*ia == 0);
			assert (*++ia == 1);
		}
		{
//			auto ia = make_forward_iterator(a); // a -> int[3]
			auto ia = make_forward_iterator(std::begin(a));
			assert (*ia == 0);
			assert (*++ia == 1);
		}
		{
			std::vector<int> va(std::begin(a), std::end(a));
			auto ia = make_forward_iterator(va.begin());
			assert (*ia == 0);
			assert (*++ia == 1);
			
		}
	}

	template<class I, class U>
	class apply_forward_iterator : public forward_iterator<U*> {
	};

#endif // _DEBUG
#if 0
	// type erasure for forward iterators
	template<class T>
	struct forward_iterator : public std::iterator<std::forward_iterator_tag, T> {
//		forward_iterator()
//		{ }
		virtual ~forward_iterator()
		{ }
		bool operator==(const forward_iterator& i) const
		{
			return _op_eq(i);
		}
		bool operator!=(const forward_iterator& i) const
		{
			return !_op_eq(i);
		}
		T operator*() const
		{
			return _op_star();
		}
		// const T& verson???
		forward_iterator& operator++()
		{
			return _pre_incr();
		}
/*		forward_iterator operator++(int)
		{
			return _post_incr();
		}
*/	private:
		virtual bool _op_eq(const forward_iterator&) const = 0;
		virtual T _op_star() const = 0;
		virtual forward_iterator& _pre_incr() = 0;
//		virtual forward_iterator _post_incr(int) = 0;
	};
	// apply function to iterator values
	template<class IT, class U>
	class apply_iterator : public forward_iterator<U> {
		using T = typename std::iterator_traits<IT>::value_type;
		IT it;
		std::function<U(T)> f;
	public:
		apply_iterator()
		{ }
		apply_iterator(const std::function<U(T)>& f, IT it)
			: it(it), f(f)
		{ }
		apply_iterator(const apply_iterator&) = default;
		apply_iterator& operator=(const apply_iterator&) = default;
		~apply_iterator()
		{ }

		bool _op_eq(const forward_iterator& i) const override
		{
			return false; // it == i.it && f == i.f; // always false !!!
		}
		U _op_star() const override
		{
			return f(*it);
		}
		apply_iterator& _pre_incr() override
		{
			++it;

			return *this;
		}
/*		apply_iterator _post_incr(int) override
		{
			apply_iterator i(*this);

			++it;

			return i;
		}
*/	};
	template<class IT, class U>
	inline apply_iterator<IT,U> make_apply_iterator(const std::function<U(typename std::iterator_traits<IT>::value_type)>& f, IT it)
	{
		return apply_iterator<IT,U>(f, it);
	}
/*	template<class IT, class F, class T = typename std::iterator_traits<IT>::value_type>
	inline auto  make_apply_iterator(const F& f, IT it) -> apply_iterator<IT,typename std::result_of<f(T)>>
	{
		return apply_iterator<IT,typename std::result_of<f(T)>>(f, it);
	}
*/
//	template<class T, class U>
//	inline forward_iterator 
#ifdef _DEBUG

	inline void test_apply_iterator()
	{
		int a[] = {0,1,2};
		{
			std::function<int(int)> sq = [](int i) { return i*i; };
			apply_iterator<int*,int> a2(sq, a);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
		{
//			auto a2 = make_apply_iterator([](int i) { return i*i; }, a); // fails!!!
//			auto sq = [](int i) { return i*i; }; // fails!!!
			std::function<int(int)> sq = [](int i) { return i*i; };
			auto a2 = make_apply_iterator(sq, a);
			assert (*a2 == a[0]*a[0]);
			++a2;
			assert (*a2 == a[1]*a[1]);
			assert (*++a2 == a[2]*a[2]);
		}
	}

#endif // _DEBUG
#endif // 0
#if 0
	// times and values
	template<class IT, class IU, 
		class T = typename std::iterator_traits<IT>::value_type,
		class U = typename std::iterator_traits<IU>::value_type>
	class pair_iterator 
		: std::iterator<std::input_iterator_tag, std::pair<T, U>> {
		IT it;
		IU iu;
	public:
		pair_iterator()
		{ }
		pair_iterator(IT it, IU iu)
			: it(it), iu(iu)
		{ }
		pair_iterator(const pair_iterator&) = default;
		pair_iterator& operator=(const pair_iterator&) = default;
		~pair_iterator()
		{ }

		bool operator==(const pair_iterator& i) const
		{
			return it == i.it && iu == i.iu;
		}
		bool operator!=(const pair_iterator& i) const
		{
			return !operator==(i);
		}
		std::pair<T,U> operator*()
		{
			return std::make_pair(*it, *iu);
		}
		pair_iterator& operator++()
		{
			++it;
			++iu;

			return *this;
		}
		pair_iterator operator++(int)
		{
			pair_iterator i(*this);

			++it;
			++iu;

			return i;
		}
	};
	template<class IT, class IU>
	inline pair_iterator<IT,IU> make_pair_iterator(IT it, IU iu)
	{
		return pair_iterator<IT,IU>(it, iu);
	}
	template<class IT, class U>
	inline pair_iterator<IT,apply_iterator<IT, U>> make_pair_iterator(const std::function<U(typename std::iterator_traits<IT>::value_type)>& f, IT it)
	{
		auto iu = make_apply_iterator(f, it);

		return pair_iterator<IT,apply_iterator<IT, U>>(it, iu);
	}
#ifdef _DEBUG

	inline void test_pair_iterator()
	{
		int a[] = {0,1,2};
		{
			auto zi = make_pair_iterator(a, a);
			assert (zi == zi);
			int i = 0;
			assert (std::make_pair(a[i],a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]) == *++zi);
		}
/*		{
			std::function<int(int)> sq = [](int i) { return i*i; };
//			auto sqa = make_apply_iterator(sq, a);
//			auto zi = make_pair_iterator(a, sqa);
			auto zi = make_pair_iterator(sq, a);
			int i = 0;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi++);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *zi);
			++i;
			assert (std::make_pair(a[i],a[i]*a[i]) == *++zi);
		}
*/	}

#endif // _DEBUG
/*
	template<class T, class X>
	class function_iterator : std::iterator<std::forward_iterator_tag, std::pair<T,X>>
*/
#endif // 0
} // timeseries