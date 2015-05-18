// enumerator.h - iter::enumerator with operator bool
// Copyright (c) KALX, LLC

#pragma once
#include <cmath>
#include <functional>
#include <iterator>
#include <type_traits>

namespace iter {

	// use has_member(size()) ???
	template<class I>
	struct enumerator_traits : public std::iterator_traits<I> {
		typedef typename I::is_counted is_counted;
	};
	template<class T>
	struct enumerator_traits<T*> : public std::iterator_traits<T*> {
		typedef std::false_type is_counted;
	};

	// iterator with operator bool() const
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	struct enumerator : public std::iterator<C,T> {
	protected:
		I i;
	public:
		typedef std::false_type is_counted;
		typedef typename std::iterator<C,T>::iterator_category iterator_category;
		typedef typename std::iterator<C,T>::value_type value_type;
		typedef typename std::iterator<C,T>::difference_type difference_type;
		typedef typename std::iterator<C,T>::pointer pointer;
		typedef typename std::iterator<C,T>::reference reference;

		enumerator()
		{ }
		enumerator(I i)
			: i(i)
		{ }

		bool operator==(const enumerator& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator& j) const
		{
			return i == j.i;
		}
		I& iterator()
		{
			return i;
		}
		I begin()
		{
			return i;
		}
		const I& begin() const
		{
			return i;
		}
		const I end() const
		{
			return nullptr;
		}

		operator bool() const
		{
			return true; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		enumerator& operator++()
		{
			++i;

			return *this;
		}
		enumerator operator++(int)
		{
			enumerator e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline enumerator<I,T> make_enumerator(I i)
	{
		return enumerator<I,T>(i);
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline enumerator<I,T> e(I i)
	{
		return enumerator<I,T>(i);
	}

	// specializations for pointers
	template<class T>
	class enumerator<T*,T> : public std::iterator<std::random_access_iterator_tag,T> {
	protected:
		T* i;
	public:
		typedef std::false_type is_counted; // for tag dispatch
		using C = std::random_access_iterator_tag;
		typedef typename std::iterator<C,T>::iterator_category iterator_category;
		typedef typename std::iterator<C,T>::value_type value_type;
		typedef typename std::iterator<C,T>::difference_type difference_type;
		typedef typename std::iterator<C,T>::pointer pointer;
		typedef typename std::iterator<C,T>::reference reference;

		enumerator()
		{ }
		enumerator(T* i)
			: i(i)
		{ }

		bool operator==(const enumerator& j) const
		{
			return i == j.i;
		}
		bool operator!=(const enumerator& j) const
		{
			return i != j.i;
		}
/*		operator T*()
		{
			return i;
		}
		operator T*() const
		{
			return i;
		}
*/		T*& iterator()
		{
			return i;
		}
		T* begin()
		{
			return i;
		}
		const T* begin() const
		{
			return i;
		}
		T* end() const
		{
			return nullptr;
		}

		operator bool() const
		{
			return true; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		enumerator& operator++()
		{
			++i;

			return *this;
		}
		enumerator operator++(int)
		{
			enumerator e(*this);

			operator++();

			return e;
		}
		enumerator& operator--()
		{
			--i;

			return *this;
		}
		enumerator operator--(int)
		{
			enumerator e(*this);

			operator--();

			return e;
		}
		enumerator& operator+=(difference_type n)
		{
			i += n;

			return *this;
		}
		enumerator& operator-=(difference_type n)
		{
			i -= n;

			return *this;
		}
		difference_type operator-(const enumerator& j) const
		{
			return i - j.i;
		}
	};

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator()
{
	int a[] = {1,2,0};

	{
		enumerator<int*> b(a), c;
		c = b;
		ensure (b == c);
		ensure (*c == *b);
		ensure (b);
		ensure (*++b == 2);
		b++; // not really the end
		ensure (b && c);
		ensure (b != c);
	}
	{
		auto b = make_enumerator(a);
		auto c(b);
		b = c;
		ensure (b);
		ensure (*++b == 2);
		b++;
		ensure (std::distance(c,b) == 2);

		int* pb = b.iterator();
		--pb;
		ensure (*pb == 2);
	}
	{
		auto b = e(a);

		for (auto c : b) {
			ensure (c == a[0]);
			break;
		}
		for (auto& c : b) {
			ensure (c == a[0]);
			break;
		}
		for (const auto& c : b) {
			ensure (c == a[0]);
			break;
		}

		auto d(b);
		
		d += 1;
		ensure (d != b);
		d += -1;
		ensure (d == b);

		d -= 1;
		ensure (d != b);
		d -= -1;
		ensure (d == b);

		ensure (d - b == 0);
	}
}

#endif // _DEBUG