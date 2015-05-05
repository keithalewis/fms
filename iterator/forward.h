// forward.h - iterators, functions, and adapters
#pragma once
#include <iterator>

namespace iterator {

	// read-only forward iterator
	template<class I, class T = typename std::iterator_traits<I>::value_type>
	class forward : public std::iterator<std::forward_iterator_tag, T> {
		I i;
	public:
		forward()
		{ }
		forward(I i)
			: i(i)
		{ }
		forward(const forward&) = default;
		forward(forward&&) = default;
		forward& operator=(forward&&) = default;
		forward& operator=(const forward&) = default;
		~forward()
		{ }

		// implement
		T operator*(void) const
		{
			return *i;
		}
		// implement
		forward& operator++()
		{
			++i;

			return *this;
		}
		// implement
		forward operator++(int)
		{
			forward i_(i);

			++i;

			return i_;
		}
	};

	template<class I>
	inline forward<I> make_forward(const I& i)
	{
		return forward<I>(i);
	}

} // forward

#ifdef _DEBUG
#include <cassert>

using namespace iterator;

inline void test_forward()
{
	int a[] = {0,1,2};

	{
		forward<int*> b(a), c;
		c = b;
		assert (*c == *b);
		c++, b++;
		assert (*c == *b);
	}
	{
		forward<int*> f(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		auto f = make_forward(std::begin(a));
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
	{
		forward<int*, double> f(a);
		assert (*f == 0);
		assert (*++f == 1);
		f++;
		assert (*f == 2);
	}
}


#endif // _DEBUG