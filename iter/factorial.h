// factorial.h - factorial enumerator
#pragma once
#include <stdexcept>
#include "accumulate.h"
#include "iota.h"

namespace iter {

	// 0!, 1!, ...
	template<class N = unsigned long long>
	class factorial_ : public enumerator<void,N,std::input_iterator_tag> {
		N n, n_; // n, n!
	public:
		factorial_()
			: n(0), n_(1)
		{
		}

		operator bool() const
		{
			return true;
		}
		N operator*() const
		{
			return n_;
		}
		factorial_& operator++()
		{
			n_ *= ++n;

			return *this;
		}
		factorial_ operator++(int)
		{
			factorial_ f(*this);

			operator++();

			return f;
		}
	};
	template<class N = unsigned long long>
	inline auto factorial()
	{
		return factorial_<N>();
	}

} // iter

#ifdef _DEBUG
#include "include/ensure.h"

using namespace iter;

inline void test_factorial()
{
	factorial_<int> f;
	ensure (*f++ == 1);
	ensure (*f == 1);
	ensure (*++f == 2);
	ensure (*++f == 6);
	ensure (*++f == 24);
	ensure (*++f == 120);
	ensure (*++f == 720);

	factorial_<int> g(f);
	f = g;
}

#endif // _DEBUG