// pochhamer.h - falling/rising factorial Pochhammer symbol
#pragma once
#include "iter/iter.h"

namespace poly {

	// Pochhammer (n > 0) and rising Pochhammer (n < 0) symbol
	template<class X = double>
	class pochhammer_ : public enumerator<void,X,std::input_iterator_tag> {
		int n;
		X x; // x
		X xi; // x(x - 1)...(x - i + 1);
	public:
		pochhammer_()
			: n(0)
		{ }
		pochhammer_(const X& x, int n)
			: n(n), x(x), xi(x)
		{
		}

		size_t size() const
		{
			return n >= 0 ? n : -n;
		}
		explicit operator bool() const
		{
			return n != 0;
		}
		X operator*() const
		{
			return xi;
		}
		pochhammer_& operator++()
		{
			if (n > 0) {
				x -= X(1);
				xi *= x;
				--n;
			}
			else if (n < 0) {
				x += X(1);
				xi *= x;
				++n;
			}

			return *this;
		}
		pochhammer_ operator++(int)
		{
			pochhammer_ p(*this);

			operator++();

			return p;
		}
	};
	template<class X = double>
	inline auto pochhammer(const X& x, int n)
	{
		return pochhammer_<X>(x, n);
	}

} // poly

#ifdef _DEBUG
#include "include/ensure.h"

inline void test_pochhammer()
{
	double x = 0.5;
	auto xn = pochhammer(x, 3);
	ensure (*xn == x);
	ensure (*++xn == x*(x - 1));
	xn++;
	ensure (*++xn == x*(x - 1)*(x - 2));
	ensure (!++xn);

	xn = pochhammer(x, -3);
	ensure (*xn == x);
	ensure (*++xn == x*(x + 1));
	xn++;
	ensure (*++xn == x*(x + 1)*(x + 2));
	ensure (!++xn);
}

#endif // _DEBUG
