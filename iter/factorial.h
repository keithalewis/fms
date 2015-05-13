// factorial.h - factorial enumerator
#pragma once
#include <stdexcept>
#include "accumulate.h"
#include "iota.h"

namespace iter {

	template<class T = double>
	class factorial : public enumerator_base<const T*,T> {
		T i, n_; // input index, n!
	public:
		factorial()
			: i(0), n_(1)
		{
		}
/*		factorial(const factorial&) = default;
		factorial(factorial&&) = default;
		factorial& operator=(const factorial&) = default;
		factorial& operator=(factorial&&) = default;
		~factorial()
		{ }
*/
		operator T*() const
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
}

#endif // _DEBUG