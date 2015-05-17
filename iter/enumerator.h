// enumerator.h - iter::enumerator with operator bool

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

	// enumerator is an iterator with operator bool() const
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	struct enumerator_base : public std::iterator<C, T> {
	public:
		typedef std::false_type is_counted; // for tag dispatch
		enumerator_base()
		{ }
		~enumerator_base()
		{ }

		// return false when done
		operator bool() const
		{
			return I::operator bool();
		}
		// not necessarily I::value_type
		T operator*(void) const
		{
			return I::operator*();
		}
		enumerator_base& operator++()
		{
			return I::operator++();
		}
		enumerator_base operator++(int)
		{
			return I::operator++(0);
		}
	};

	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class enumerator : public enumerator_base<I,T,C> {
	protected:
		I i;
	public:
		typedef typename enumerator_traits<I>::is_counted is_counted; // for tag dispatch
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
		operator I()
		{
			return i;
		}
		I& iterator()
		{
			return i;
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

	// specializations for pointers
	template<class T>
	class enumerator<T*,T> : public enumerator_base<T*,T> {
	protected:
		T* i;
	public:
		typedef std::false_type is_counted; // for tag dispatch
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
		operator T*() const
		{
			return i;
		}
		T*& iterator()
		{
			return i;
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
		auto e = make_enumerator(a);
		ensure (e);
		ensure (*++e == 2);
		e++;

		int* pe = e;
		--pe;
		ensure (*pe == 2);
	}
}

#endif // _DEBUG