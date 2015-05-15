// counted.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// counted enumerator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class counted_enumerator : public enumerator<I,T> {
		mutable size_t n;
	public:
		using enumerator<I,T>::i;

		counted_enumerator()
		{ }
		counted_enumerator(I i, size_t n)
			: enumerator<I,T>(i), n(n)
		{ }

		size_t size() const
		{
			return n;
		}
		operator bool() const
		{
			return n != 0;
		}
		T operator*() const
		{
			return *i;
		}
		counted_enumerator& operator++()
		{
			++i;
			--n;

			return *this;
		}
		counted_enumerator operator++(int)
		{
			counted_enumerator e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline counted_enumerator<I,T> make_counted_enumerator(I i, size_t n)
	{
		return counted_enumerator<I,T>(i, n);
	}
	// shorthand
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline counted_enumerator<I,T> e(I i, size_t n)
	{
		return counted_enumerator<I,T>(i, n);
	}
	// specialization
/*	template<class T, size_t N>
	class counted_enumerator<T(&)[N],T> {
		T* i;
		size_t n;
	public:
		counted_enumerator()
		{ }
		counted_enumerator(T (&i)[N])
			: i(i), n(N)
		{ }
		operator T*()
		{
			return i;
		}
		operator bool() const
		{
			return n != 0; // infinite
		}
		T operator*() const
		{
			return *i;
		}
		counted_enumerator& operator++()
		{
			++i;
			--n;

			return *this;
		}
		counted_enumerator operator++(int)
		{
			counted_enumerator e(*this);

			operator++();

			return e;
		}
	};
*/
} // iter


#ifdef _DEBUG
#include <cassert>

using namespace iter;

inline void test_enumerator_counted()
{
	int a[] = {1,2,0};

	{
		auto e = make_counted_enumerator(a, 2);
		assert (e);
		assert (*++e == 2);
		assert (e);
		e++;
		assert (!e);
	}
	{
		char foo[] = "foo";
		auto n = e(foo, 3);
		assert (*n++ == 'f' && *n++ == 'o' && *n++ == 'o' && !n);
	}
}

#endif // _DEBUG