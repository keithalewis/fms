// range.h - range iterators with sentinal
#pragma once
#ifdef _DEBUG
#include <cassert>
#include <vector>
#endif
#include <functional>
#include <iterator>

namespace range {

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class iterator : public std::iterator<std::forward_iterator_tag, T> {
		I i;
	public:
		iterator()
		{ }
		iterator(const I& i)
			: i(i)
		{ }
		iterator(const iterator&) = default;
		iterator& operator=(const iterator&) = default;
		~iterator()
		{ }

		// implement
		bool operator==(const iterator& i) const
		{
			return i.operator==(i);
		}
		bool operator!=(const iterator& i) const
		{
			return !operator==(i);
		}
		// implement
		T operator*(void) const
		{
			return *i;
		}
		// implement
		iterator& operator++()
		{
			++i;

			return *this;
		}
		// implement
		iterator operator++(int)
		{
			iterator i_(i);

			++i;

			return i_;
		}
	};
	template<class I>
	inline iterator<I> make_iterator(const I& i)
	{
		return iterator<I>(i);
	}

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	struct enumerator : public iterator<I, T> {
		using iterator<I>::iterator;

		enumerator()
		{ }
		enumerator(const enumerator&) = default;
		enumerator& operator=(const enumerator&) = default;
		~enumerator()
		{ }
		// works for null terminated arrays
		virtual operator bool() const
		{
			return iterator<I>::operator*() != T(0);
		}
	};
	template<class I>
	inline enumerator<I> make_enumerator(const I& i)
	{
		return enumerator<I>(i);
	}

	template<class I, class J,
		class T = typename std::common_type<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>::type>
	class concatenate : public iterator<J, T> {
		I i;
		J j;
	public:
		concatenate(I i, J j)
			: i(i), j(j)
		{ }
		concatenate(const concatenate&) = default;
		concatenate& operator=(const concatenate&) = default;
		~concatenate()
		{ }

		bool operator==(const concatenate& k) const
		{
			return i == k.i && j == k.j;
		}
		T operator*() const
		{
			return i ? *i : *j;
		}
		concatenate& operator++()
		{
			i ? ++i : ++j;

			return *this;
		}
		concatenate operator++(int)
		{
			concatenate k(*this);

			operator++();

			return k;
		}
	};
	template<class I, class J,
		class T = typename std::common_type<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>::type>
	inline concatenate<I,J,T> make_concatenate(I i, J j)
	{
		return concatenate<I,J,T>(i, j);
	}
/*
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class cycle : public iterator<T*> {
		std::vector<I> i;
		size_t at;
	public:
		cycle(const std::initializer_list<I>& i)
			: i(i.begin(), i.end()), at(0)
		{ }
		~cycle()
		{ }
		bool operator==(const cycle& i_) const
		{
			return i == i_.i && at == i_.at;
		}
		T operator*() const
		{
			return *i[at];
		}
		cycle& operator++()
		{
			for (size_t j = (at + 1)) {

			}
		}
	};
*/
#ifdef _DEBUG
	inline void test_iterator()
	{
		int a[] = {0,1,2};

		{
			iterator<int*> ia(a);
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
		}
		{
//			auto ia = make_iterator(a); // a -> int[3]
//			auto ia = make_iterator(std::begin(a)); // ok
			auto ia = make_iterator(&a[0]);
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
		}
		{
			std::vector<int> va(std::begin(a), std::end(a));
			auto ia = make_iterator(va.begin());
			assert (*ia++ == 0);
			assert (*ia == 1);
			assert (*++ia == 2);
		}
	}
	template<class I>
	inline int sum(enumerator<I> e)
	{
		int i = 0;
		while (e)
			i += *e++;

		return i;
	}
	inline void test_enumerator()
	{
		{
			int a[] = {1,2,3,0};
			auto e = make_enumerator(&a[0]);
			assert (6 == sum(e));
			assert (*e == 1);
			++e;
			assert (*e == 2);
			assert (*e++ == 2);
			assert (*e == 3);
		}
		{
			std::vector<int> a {1,2,3,0};
			assert (6 == sum(make_enumerator(a.begin())));
		}
	}
	inline void test_concatenate()
	{
		int i[] = {1,2,0};
		int j[] = {3,4};

		{
			concatenate<enumerator<int*>,iterator<int*>> c(make_enumerator(&i[0]), make_iterator(&j[0]));
			assert (*c == 1);
			assert (*++c == 2);
			assert (*++c == 3);
			c++;
			assert (*c == 4);
		}
		{
			auto c = make_concatenate(make_enumerator(&i[0]), make_iterator(&j[0]));
			assert (*c == 1);
			assert (*++c == 2);
			assert (*++c == 3);
			c++;
			assert (*c == 4);
		}
	}

#endif // _DEBUG
} // range
