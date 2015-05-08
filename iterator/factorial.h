// factorial.h - factorial enumerator
#pragma once
#include <limits>
#include "input.h"

namespace iterator {

	template<class T>
	class factorial : public input<const T*,T> {
		T i, n_;
	public:
		factorial(const T& i = T(0))
			: i(i), n_(1)
		{ }
		factorial(const factorial&) = default;
		factorial(factorial&&) = default;
		factorial& operator=(const factorial&) = default;
		factorial& operator=(factorial&&) = default;
		~factorial()
		{ }

		bool operator!=(const factorial& f) const
		{
			return i != f.i || n_ != f.n_;
		}
		T operator*() const
		{
			return n_;
		}
		factorial& operator++()
		{
			n_ *= ++i;

			return *this;
		}
		factorial operator++(int)
		{
			factorial f(*this);

			operator++();

			return f;
		}
	};

} // iterator

#ifdef _DEBUG
#include <cassert>

using namespace iterator;

inline void test_factorial()
{
	factorial<int> f;
	assert (*f++ == 1);
	assert (*f == 1);
	assert (*++f == 2);
	assert (*++f == 6);
	assert (*++f == 24);
	assert (*++f == 120);
	assert (*++f == 720);
}

#endif // _DEBUG