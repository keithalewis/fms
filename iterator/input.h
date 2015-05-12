// input.h - iterators, functions, and adapters
#pragma once
#include <iterator>

namespace iter {

	// read-only input iterator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class input_base : public std::iterator<std::input_iterator_tag, T> {
	public:
		input_base()
		{ }
		~input_base()
		{ }

		// not necessarily I::value_type
		T operator*(void) const
		{
			return I::operator*();
		}
		input_base& operator++()
		{
			return I::operator++();
		}
		input_base operator++(int)
		{
			return I::operator++(0);
		}
	};

	// provide the actual iterator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class input : public input_base<I,T> {
		I i;
	public:
		input()
		{ }
		input(I i)
			: i(i)
		{ }
		input(const input&) = default;
		input(input&&) = default;
		input& operator=(input&&) = default;
		input& operator=(const input&) = default;
		~input()
		{ }
	
		// for operator== and operator!=
		operator I() const
		{
			return i;
		}

		T operator*() const
		{
			return *i;
		}
		input& operator++()
		{
			++i;

			return *this;
		}
		input operator++(int)
		{
			input i_(i);

			++i;

			return i_;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline input<I> make_input(I i)
	{
		return input<I,T>(i);
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline input<I> i(I i)
	{
		return input<I,T>(i);
	}

	// reverse input
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class rinput : public input_base<I,T> {
		I i;
	public:
		rinput()
		{ }
		rinput(I i)
			: i(--i) // just like reverse iterators
		{ }
		rinput(const rinput&) = default;
		rinput(rinput&&) = default;
		rinput& operator=(rinput&&) = default;
		rinput& operator=(const rinput&) = default;
		~rinput()
		{ }
	
		// for operator== and operator!=
		operator I() const
		{
			return i;
		}

		T operator*() const
		{
			return *i;
		}
		rinput& operator++()
		{
			--i;

			return *this;
		}
		rinput operator++(int)
		{
			rinput i_(*this);

			--i;

			return i_;
		}
	};
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline rinput<I> make_rinput(I i)
	{
		return rinput<I,T>(i);
	}
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	inline rinput<I> ri(I i)
	{
		return rinput<I,T>(i);
	}

} // input

#ifdef _DEBUG
#include <cassert>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace iter;

inline void test_input()
{
	int a[] = {0,1,2};

	{
		input<int*> b(a), c;
		c = b;
		assert (*c == *b);
		c++, b++;
		assert (*c == *b);

		c = make_input(a);
		c = make_input(&a[0]);
		c = make_input(std::begin(a));

		assert (c != b);
		c = b;
		assert (c == b);
		c = make_input(a);
		assert (c == a);
	}
	{
		input<int*> f(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		auto f = make_input(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		input<int*, double> f(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		const int a0[] = {0,1,2}, a1[] = {3,4};
		std::vector<input<const int*>> a(2);
		a[0] = make_input(&a0[0]);
		a[1] = make_input(&a1[0]);

		auto b = make_input(a.begin());
		auto c = *b;
		assert (*c == 0);
		assert (*++c == 1);
		++c;
		assert (*c == 2);

		c = *++b;
		assert (*c == 3);
		assert (*++c == 4);
	}
	{
		const int a0[] = {0,1,2}, a1[] = {3,4};
		input<const int*> a[2];
		a[0] = make_input(a0);
		a[1] = make_input(a1);

		auto b = make_input(a);
		auto c = *b;
		assert (*c == 0);
		assert (*++c == 1);
		++c;
		assert (*c == 2);

		c = *++b;
		assert (*c == 3);
		assert (*++c == 4);
	}
	{
		// plays nice with STL
		auto b = make_input(std::begin(a));
		auto e = make_input(std::end(a));
		assert (3 == std::accumulate(b, e, 0));
	}
	{
		int a[] = {1,2,3};
		auto e = make_rinput(a + 3);
		assert (*e++ == 3);
		assert (*e == 2);
		assert (*++e == 1);

		auto b = make_input(a);
		e = make_rinput(a + 3);
		int s = 0;
		s += *b++ * *e++;
		s += *b++ * *e++;
		s += *b++ * *e++;

		assert (s == 1*3 + 2*2 + 3*1);
	}
}

#endif // _DEBUG
