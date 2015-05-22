// counted.h - enumerators with a count
#pragma once
#include <vector>
#include "../enumerator.h"

namespace iter {

	// counted enumerator
	template<class I, 
		class T = typename std::iterator_traits<I>::value_type,
		class C = typename std::iterator_traits<I>::iterator_category
	>
	class counted_enumerator : public enumerator<I,T,C> {
		size_t n;
	public:
		typedef std::true_type is_counted;
		using enumerator<I,T,C>::i;

		counted_enumerator()
		{ }
		counted_enumerator(I i, size_t n)
			: enumerator<I,T,C>(i), n(n)
		{ }
		size_t size() const
		{
			return n;
		}
		I begin()
		{
			return i;
		}
		I end()
		{
			I e(i);

			std::advance(e, n);
	
			return e;
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
	inline counted_enumerator<I,T> ce(I i, size_t n)
	{
		return counted_enumerator<I,T>(i, n);
	}

	// specialization
	template<class T, size_t N>
	class counted_enumerator<T(&)[N]> : public enumerator<T*,T,std::random_access_iterator_tag> {
		size_t n;
	public:
		typedef std::true_type is_counted;
		using enumerator<T*,T,std::random_access_iterator_tag>::i;

		counted_enumerator()
		{ }
		counted_enumerator(T(&i)[N])
			: enumerator<T*,T,std::random_access_iterator_tag>(i), n(N)
		{ }

		size_t size() const
		{
			return n;
		}
		T* end()
		{
			T* e(i);

			std::advance(e, n);

			return e;
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
/*	template<class T>
	inline auto ce(const std::vector<T>& v)
	{
		return make_counted_enumerator(v.begin(), v.size());
	}
*/
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
		ensure (e == f);
		ensure (e.size() == 2);
		ensure (*++e == 2);
		ensure (e.size() == 1);
		ensure (e);
		e++;
		ensure (!e);
		ensure (e.size() == 0);
	}
	{
		char foo[] = "foo";
		auto n = ce(foo, 3);
		ensure (*n++ == 'f' && *n++ == 'o' && *n++ == 'o' && !n);
		n = ce(foo);
		ensure (n.size() == 4);
		ensure (n[3] == 0);
		auto o = ce("foo");
		ensure (o.size() == 4);
	}
	{
		auto b = ce(a);
		ensure (b.size() == 3);
		ensure (b.end()[-1] == 3);
		b += 2;
		ensure (*b == 3);
		b -= 2;
		ensure (*b == 1);
	}
/*	{
		std::vector<int> a = {1,2,3};
		auto b = ce(a);
		ensure (b.size() == a.size());
		ensure (*b == a[0]);
		ensure (*++b == a[1]);
		b++;
		ensure (*b == a[2]);
		ensure (!++b);
	}
*/
}

#endif // _DEBUG