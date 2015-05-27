// counted.h - enumerators with a count
#pragma once
#include <utility>
#include <vector>
#include "../enumerator.h"

namespace iter {

	// counted enumerator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class counted_enumerator_ : public enumerator_<I,T> {
	protected:
		size_t n;
	public:
		using enumerator_<I,T>::i;

		counted_enumerator_()
		{ }
		counted_enumerator_(I i, size_t n)
			: enumerator_<I,T>(i), n(n)
		{ }

		size_t size() const
		{
			return n;
		}

		I iterator() const
		{
			return i;
		}
		counted_enumerator_ begin() const
		{
			return *this;
		}
		// hide enumerator_::end
		counted_enumerator_ end() const
		{
			I e(i);

			std::advance(e, n);
	
			return counted_enumerator_(e, 0);
		}

		explicit operator bool() const
		{
			return n != 0;
		}
		T operator*() const
		{
			return *i;
		}
		counted_enumerator_& operator++()
		{
			++i;
			--n;

			return *this;
		}
		counted_enumerator_ operator++(int)
		{
			counted_enumerator_ e(*this);

			operator++();

			return e;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto counted_enumerator(I i, size_t n)
	{
		return counted_enumerator_<I,T>(i, n);
	}
	// shorthand
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline auto ce(I i, size_t n)
	{
		return counted_enumerator_<I,T>(i, n);
	}

	// specialization
	template<class T, size_t N>
	class counted_enumerator_<T(&)[N]> : public enumerator_<T*,T> {
		size_t n;
	public:
		using enumerator_<T*,T>::i;

		counted_enumerator_()
		{ }
		counted_enumerator_(T(&i)[N])
			: enumerator_<T*,T>(i), n(N)
		{ }

		size_t size() const
		{
			return n;
		}

		T* iterator() const
		{
			return i;
		}
		counted_enumerator_ begin() const
		{
			return *this;
		}
		counted_enumerator_ end()
		{
			return counted_iterator(i + n, 0);
		}

		explicit operator bool() const
		{
			return n != 0;
		}
		T operator*() const
		{
			return *i;
		}
		counted_enumerator_& operator++()
		{
			++i;
			--n;

			return *this;
		}
		counted_enumerator_ operator++(int)
		{
			counted_enumerator_ e(*this);

			operator++();

			return e;
		}
	};
	template<class T, size_t N>
	inline auto counted_enumerator(T(&i)[N])
	{
		return counted_enumerator(i, N);
	}
	// shorthand
	template<class T, size_t N>
	inline auto ce(T(&i)[N])
	{
		return counted_enumerator(i, N);
	}

	// containers
	template<class C>
	inline auto ce(const C& c)
	{
		return counted_enumerator(c.begin(), c.size());
	}
} // iter


#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_enumerator_counted()
{
	int a[] = {1,2,3};

	{
		auto e = counted_enumerator(a, 2);
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
		ensure (n.iterator()[3] == 0);
		auto o = ce("foo");
		ensure (o.size() == 4);
	}
	{
		auto b = ce(a);
		ensure (b.size() == 3);
//		ensure (b.end()[-1] == 3);
		int i = 0;
		for (auto c : b) {
			ensure (c == a[i++]);
		}
		i = 0;
//		for (auto& c : b) {
//			ensure (c == a[i++]);
//		}
		i = 0;
		for (const auto& c : b) {
			ensure (c == a[i++]);
		}

		int* c = b.iterator();
		c += 2;
		ensure (*c == 3);
		c -= 2;
		ensure (*c == 1);
	}
	{
		std::vector<int> a = {1,2,3};
		auto b = ce(a);
		ensure (b.size() == a.size());
		ensure (*b == a[0]);
		ensure (*++b == a[1]);
		b++;
		ensure (*b == a[2]);
		ensure (!++b);

		int i = 0;
		b = ce(a);
		for (auto c : b) {
			ensure (c == a[i++]);
		}
//		for (auto& c : b) {
//			ensure (c == a[i++]);
//		}
		i = 0;
		for (const auto& c : b) {
			ensure (c == a[i++]);
		}
	}

}

#endif // _DEBUG