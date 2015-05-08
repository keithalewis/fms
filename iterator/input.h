// input.h - iterators, functions, and adapters
#pragma once
#include <iterator>

namespace iterator {

	// read-only input iterator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class input : public std::iterator<std::input_iterator_tag, T> {
	protected:
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

		// implement
		T operator*(void) const
		{
			return *i;
		}
		// implement
		input& operator++()
		{
			++i;

			return *this;
		}
		// implement
		input operator++(int)
		{
			input i_(i);

			++i;

			return i_;
		}
	};

	template<class I>
	inline input<I> make_input(const I& i)
	{
		return input<I>(i);
	}

} // input

#ifdef _DEBUG
#include <cassert>

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
	}
	{
		input<int*> f(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		auto f = make_input(std::begin(a));
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
}


#endif // _DEBUG
