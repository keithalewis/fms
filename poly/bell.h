// bell.h - Complete Bell polynomials
#pragma once
#include <vector>
#include "iter/iter.h"

namespace poly {

	template<class K, class X = typename std::iterator_traits<K>::value_type>
	class bell_ : public enumerator_<void,X,std::input_iterator_tag> {
		concatenate_<K,constant_<X>> x;
		X n;
		std::vector<X> B;
	public:
		bell_()
		{ }
		// extend x with 0's
		bell_(K x)
			: x(concatenate(x,c(X(0)))), n(X(0)), B({X(1)})
		{ }

		explicit operator bool() const
		{
			return true;
		}
		X operator*() const
		{
			return B.back();
		}
		// B(n + 1, x[0], ... x[n]) = sum_{0 <= k <= n}
		//	 choose(n,k) B(n-k,x[0],...,x[n-k]) x[k+1]
		bell_& operator++()
		{
			B.push_back(sum0(choose(n)*re(B.end())*x));

			++n;

			return *this;
		}
		bell_ operator++(int)
		{
			bell_ b_(*this);

			operator++();

			return b_;
		}
	};
	template<class K, class X = typename std::iterator_traits<K>::value_type>
	inline auto bell(K k)
	{
		return bell_<K,X>(k);
	}

	// B(n + 1, x[0], ... x[n]) = sum { choose(n,k) B(n-k,x[0],...,x[n-k]) x[k+1] : 0 <= k <= n }
	template<class Y, class X = double>
	X Bell(size_t n, Y x)
	{
		if (n == 0)
			return 1;

		std::vector<X> b(n + 1);
		b[0] = X(1);

		for (size_t k = 1; k <= n; ++k)
			b[k] = sum0(choose(k-1) * re(&b[k]) * x);

		return b[n];
	}

} // bell

#ifdef _DEBUG
#include <algorithm>
#include <random>
#include <vector>
#include "include/ensure.h"

using namespace std;
using namespace poly;

inline void test_bell()
{
	default_random_engine dre;
	uniform_real_distribution<> u(-1,1);
	vector<double> x(9,1);

	// http://en.wikipedia.org/wiki/Bell_number
	ensure (Bell<>(0, &x[0]) == 1);
	ensure (Bell<>(1, &x[0]) == 1);
	ensure (Bell<>(2, &x[0]) == 2);
	ensure (Bell<>(3, &x[0]) == 5);
	ensure (Bell<>(4, &x[0]) == 15);
	ensure (Bell<>(5, &x[0]) == 52);
	ensure (Bell<>(6, &x[0]) == 203);
	ensure (Bell<>(7, &x[0]) == 877);
	ensure (Bell<>(8, &x[0]) == 4140);

	// B(0) = 1, B(1,x1) = x1
	ensure (Bell<>(0, iota(1)) == 1);
	ensure (Bell<>(1, iota(1)) == 1);
	// B(2,x1,x2) = B(1,x1)x1 + B(0)x2 = x1^2 + x2
	ensure (Bell<>(2, iota(1)) == 1*1 + 2);
	// B(3,x1,x2,x3) 
	// = B(2,x1,x2) x1 + 2 B(1,x1) x2 + B(0) x3
	// = (x1^2 + x2) x1 + 2 x1 x2 + x3
	// = x1^3 + 3 x1 x2 + x3
	ensure (Bell<>(3, iota(1)) == 1*1*1 + 3*1*2 + 3);
	// B(4,x1,x2,x3,x4)
	// = B(3) x1 + 3B(2) x2 + 3B(1) x3 + B(0) x4
	// = (x1^3 + 3 x1 x2 + x3) x1 + 3(x1^2 + x2) x2 + 3 x1 x3 + x4
	// = x1^4 + 6 x1^2 x2 + 4 x1 x3 + 3 x2^2 + x4
	ensure (Bell<>(4, iota(1)) == 1*1*1*1 + 6*1*1*2 + 4*1*3 + 3*2*2+ 4);
	// B(5,x1,x2,x3,x4,x5)
	// = B(4) x1 + 4B(3) x2 + 6B(2) x3 + 4B(1) x4 + x5
	// = (x1^4 + 6 x1^2 x2 + 4 x1 x3 + 3 x2^2 + x4) x1 
	//    + 4(x1^3 + 3 x1 x2 + x3) x2 + 6(x1^2 + x2) x3 + 4 x1 x4 + x5
	// = x1^5 + 10 x1^3 x2 + 10 x1^2 x3 + 15 x1 x2^2 + 5 x1 x4 + 4 x2 x3 + x5
//	ensure (Bell<>(5, iota(1)) == 1 + 10*2 + 10*3 + 15*2*2 + 5*4 + 4*2*3 + 5);

//	generate(begin(x), end(x), [&dre,u](void) { return u(dre); });


	auto b = bell(iota<double>(1));
	int i = 0;
	ensure (*b == Bell<>(i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
	ensure (*++b == Bell<>(++i, iota<double>(1)));
}

#endif // _DEBUG
