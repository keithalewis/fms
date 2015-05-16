// counted.h
#pragma once
#include "../enumerator.h"

namespace iter {

	// counted enumerator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class counted_enumerator : public enumerator_base<I,T> {
		I i;
		size_t n;
	public:
		counted_enumerator()
		{ }
		counted_enumerator(I i, size_t n)
			: i(i), n(n)
		{ }

		size_t size() const
		{
			return n;
		}
		I end()
		{
			std::advance(i, n);

			return i;
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
	template<class T, size_t N>
	class counted_enumerator<T(&)[N]> : public enumerator_base<T*,T> {
		T* i;
		size_t n;
	public:
		counted_enumerator()
		{ }
		counted_enumerator(T(&i)[N])
			: i(i), n(N)
		{ }

		size_t size() const
		{
			return n;
		}
		T* end()
		{
			std::advance(i, n);

			return i;
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
	template<class T, size_t N>
	inline auto make_counted_enumerator(T(&i)[N])
	{
		return make_counted_enumerator(i, N);
	}
	// shorthand
	template<class T, size_t N>
	inline auto ce(T(&i)[N])
	{
		return make_counted_enumerator(i, N);
	}


} // iter


#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_counted()
{
	int a[] = {1,2,3};

	{
		auto e = make_counted_enumerator(a, 2);
		auto f(e);
		e = f;
		ensure (e);
		ensure (*++e == 2);
		ensure (e);
		e++;
		ensure (!e);
	}
	{
		char foo[] = "foo";
		auto n = e(foo, 3);
		ensure (*n++ == 'f' && *n++ == 'o' && *n++ == 'o' && !n);
	}
	{
		auto b = ce(a);
		ensure (b.size() == 3);
		ensure (b.end()[-1] == 3);
	}
}

#endif // _DEBUG