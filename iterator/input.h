// input.h - iterators, functions, and adapters
#pragma once
#include <iterator>
//#include <initializer_list>

namespace iterator {

	// read-only input iterator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class input_base : public std::iterator<std::input_iterator_tag, T> {
	public:
		input_base()
		{ }
		~input_base()
		{ }
/*
		operator I()
		{
			return I::operator I();
		}
*/
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

	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class input : public input_base<I,T> {
	public:
		I i;
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
} // input

#ifdef _DEBUG
#include <cassert>
#include <algorithm>
#include <numeric>
#include <vector>

using namespace iterator;

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
		auto b = make_input(std::begin(a));
		auto e = make_input(std::end(a));
		assert (3 == std::accumulate(b, e, 0));
	}
}

#endif // _DEBUG
