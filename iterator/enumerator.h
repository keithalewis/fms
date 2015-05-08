// enumerator.h - iterator::enumerator with operator bool
#pragma once
#include <functional>
#include <iterator>
#include <type_traits>
#include "input.h"

namespace iterator {

	// read-only input iterator with sentinel
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class enumerator : public input<I,T> {
		std::function<bool(const I&)> e; // false when done
	public:
		enumerator()
		{ }
		enumerator(const enumerator&) = default;
		enumerator(enumerator&&) = default;
		enumerator& operator=(enumerator&&) = default;
		enumerator& operator=(const enumerator&) = default;
		~enumerator()
		{ }

		// default infinite
		enumerator(I i)
			: input<I,T>(i), e([](const I&) { return true; })
		{ }
		// counted or null terminated if n = 0
		enumerator(I i, size_t n)
			: input<I,T>(i)
		{
			if (n)
				e = [n](const I&) mutable { return n-- != 0; };
			else
				e = [](const I& i) { return *i != 0; };
		}
		enumerator(I i, const std::function<bool(const I&)>& e)
			: input<I,T>(i), e(e)
		{ }

		operator const I&() const
		{
			return input<I,T>::i;
		}
		bool operator==(const I& i) const
		{
			return input<I,T>::i == i;
		}
		bool operator!=(const I& i) const
		{
			return !operator==(i);
		}

		operator bool() const
		{
			return e(input<I,T>::i);
		}
		T operator*() const
		{
#ifdef _DEBUG
			if (!e(input<I,T>::i))
				throw std::out_of_range("iterator::enumerator::operator*(): out of range");
#endif
			return *input<I,T>::i;
		}
		enumerator& operator++()
		{
			++input<I,T>::i;

			return *this;
		}
		enumerator operator++(int)
		{
			enumerator i_(input<I,T>::i);

			operator++();

			return i_;
		}
	};

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline enumerator<I,T> make_enumerator(I i)
	{
		return enumerator<I,T>(i);
	}

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline enumerator<I,T> make_enumerator(I i, size_t n)
	{
		return enumerator<I,T>(i, n);
	}
	/*
	template<class C>
	struct has_begin {
		template<typename C, size_t (C::*)() const> struct SFINAE {};
		template<typename C> static char test(SFINAE<C, &C::begin>*);
		template<typename C> static int test(...);
		static const bool yes = sizeof(test<C>(0)) == sizeof(char);
	};
	*/
	template<class C>
	inline	enumerator<typename C::iterator,typename C::value_type>
	make_enumerator(C c)
	{
		return enumerator<typename C::iterator,typename C::value_type>(std::begin(c), std::end(c));
	}
	
} // iterator

#ifdef _DEBUG
#include <cassert>
#include <vector>

using namespace iterator;

inline void test_enumerator()
{
	int a[] = {1,2,0};

	{
		enumerator<int*> b(a), c;
		c = b;
		assert (b == c);
		assert (*c == *b);
		assert (b);
		assert (*++b == 2);
		b++;
		assert (b && c);
		assert (b != c);
	}
	{
		auto e = make_enumerator(a);
		assert (e);
		assert (*++e == 2);
		e++;
	}
	{
		auto count = [](enumerator<const char*> e) { 
			int c = 0; 
			while (e) { 
				++e; 
				++c; 
			} return c; 
		};
		auto e = make_enumerator("foo", 0);
		assert (3 == count(e));
		assert (2 == count(make_enumerator("bar", 2)));
	}
	{
		auto e = make_enumerator(a, 0);
		assert (e);
		assert (*++e == 2);
		e++;
		//assert (*e == 0); // throws
		assert (!e);
	}
/*	{
		std::vector<int> b(std::begin(a), std::end(a));
		auto e = make_enumerator(b);
		assert (e);
		assert (*++e == 2);
		e++;
		assert (*e++ == 0);
		assert (!e);
	}
*/
}

#endif // _DEBUG