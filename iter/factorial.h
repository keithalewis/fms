// factorial.h - factorial enumerator
#pragma once
#include <stdexcept>
#include "input.h"

namespace iter {

	// (a0 + a1 n + a2 n^2)!
	template<class T = double>
	class factorial : public enumerator_base<const T*,T> {
		T i, n_; // input index, n!
		T a0, a1, a2;
	public:
		factorial(const T& a0 = T(0), const T& a1 = T(1), const T& a2 = T(0))
			: i(0), n_(1), a0(a0), a1(a1), a2(a2)
		{
			if (a2 < 0 || (a2 > 0 && (a0 < 0 || a1 < 0)))
				throw std::runtime_error("iter::factorial: a0 + a1 n + a2 n^2 must be increasing in n");

			// a0!
			for (T j = 1; j <= a0; ++j)
				n_ *= j;
		}
/*		factorial(const factorial&) = default;
		factorial(factorial&&) = default;
		factorial& operator=(const factorial&) = default;
		factorial& operator=(factorial&&) = default;
		~factorial()
		{ }
*/
		operator T*()
		{
			return &n_;
		}
		operator bool() const
		{
			return true;
		}
		T operator*() const
		{
			return n_;
		}
		factorial& operator++()
		{
			T j = a0 + i*(a1 + i*a2);
			++i;
			T n = a0 + i*(a1 + i*a2);
			while (++j <= n)
				n_ *= j;

			return *this;
		}
		factorial operator++(int)
		{
			factorial f(*this);

			operator++();

			return f;
		}
	};

} // iter

#ifdef _DEBUG
#include <cassert>

using namespace iter;

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

	factorial<int> g(f);
	f = g;

	factorial<int> h(1, 0, 1); // (1 + n^2)!
	assert (*h == 1);
	assert (*++h == 2);
	assert (*++h == 5*4*3*2);
}

#endif // _DEBUG