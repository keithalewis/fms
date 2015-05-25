// enumerator.h - iter::enumerator with operator bool
// Copyright (c) KALX, LLC

#pragma once
#include <cmath>
#include <functional>
#include <iterator>
#include <type_traits>

namespace iter {

	// iterator with operator bool() const
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	struct enumerator : public std::iterator<C,T> { // !!!need to specialize for all categories
	protected:
		I i;
	public:
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
			return i != j.i;
		}
/*		operator I()
		{
			return i;
		}
		operator I&()
		{
			return i;
		}
*/		I& iterator()
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

	// specialize for empty iterators
	template<class T>
	struct enumerator<void,T,std::input_iterator_tag> : public std::iterator<std::input_iterator_tag,T> {
	};

	// specializations for pointers
	template<class T>
	class enumerator<T*,T> : public std::iterator<std::random_access_iterator_tag,T> {
	protected:
		T* i;
	public:
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
		operator const T*()
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
		T& operator[](difference_type n)
		{
			return i[n];
		}
		const T& operator[](difference_type n) const
		{
			return i[n];
		}
	};
	// specializations for pointers
	template<class T>
	class enumerator<const T*,T> : public std::iterator<std::random_access_iterator_tag,T> {
	protected:
		const T* i;
	public:
		using C = std::random_access_iterator_tag;
		typedef typename std::iterator<C,T>::iterator_category iterator_category;
		typedef typename std::iterator<C,T>::value_type value_type;
		typedef typename std::iterator<C,T>::difference_type difference_type;
		typedef typename std::iterator<C,T>::pointer pointer;
		typedef typename std::iterator<C,T>::reference reference;

		enumerator()
		{ }
		enumerator(const T* i)
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
/*		operator const T*()
		{
			return i;
		}
		operator T*()
		{
			return i;
		}
		operator T*() const
		{
			return i;
		}
*/		const T* iterator() const
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
/*		T& operator[](difference_type n)
		{
			return i[n];
		}
*/		const T& operator[](difference_type n) const
		{
			return i[n];
		}
	};

} // iter

#ifdef _DEBUG
#include "include/ensure.h"
#include <vector>

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
	{
		std::vector<int> a = {1,2,3};
		auto b = e(a.begin());
		ensure (*b == 1);
		ensure (*++b == 2);
		b++;
		ensure (*b == 3);
		b = a.begin();
//		auto c = e(a.end());
//		ensure (std::distance(b,c) == a.size()); // operator bool() called!!!
	}
}

#endif // _DEBUG