// dual.h - dual numbers for computing machine precision derivatives
#pragma once
#include <algorithm>
#include <functional>
#include <vector>

namespace dual {

	namespace detail {
		template<class X = double>
		inline X factorial(size_t n)
		{
			static std::vector<X> n_ = {1,1,2,6,24,120,720};

			if (n >= n_.size()) {
				for (X i = n_.size(); i <= n; ++i)
					n_.push_back(n_.back()*i);
			}

			return n_[n];
		}
	}

	template<class X>
	class number : public std::vector<X> {
	public:
		using std::vector<X>::vector;

		// x0 + 0 J + 0 J^2 + ... + 0 J^{n-1}
		number(size_t n, const X& x)
			: std::vector<X>(n)
		{
			operator[](0) = x;
		}

		// i-th derivative
		X operator()(size_t i) const
		{
			return operator[](i)/detail::factorial<X>(i);
		}

		// scalar operators
		template<class Op>
		number& op(const X& a)
		{
			std::transform(this->begin(), this->end(), this->begin(), [a](const X& xi) { return Op{}(xi,a); });

			return *this;
		}
		number& operator+=(const X& a)
		{
			return op<std::plus<X>>(a);
		}
		number& operator-=(const X& a)
		{
			return op<std::minus<X>>(a);
		}
		number& operator*=(const X& a)
		{
			return op<std::multiplies<X>>(a);
		}
		number& operator/=(const X& a)
		{
			return op<std::divides<X>>(a);
		}

		// vector operations
		template<class Op>
		number& op(const number& y)
		{
			if (y.size() > size())
				resize(y.size());

			for (size_t i = 0; i < y.size(); ++i)
				operator[](i) = Op{}(operator[](i), y[i]);

			return *this;
		}
		number& operator+=(const number& y)
		{
			return op<std::plus<X>>(y);
		}
		number& operator-=(const number& y)
		{
			return op<std::minus<X>>(y);
		}
		// (x*y)[j] = sum_{i=0}^j x[i]*y[j-i]
		number& operator*=(const number& y)
		{
			if (y.size() > size())
				resize(y.size());

			std::vector<X> z(n);
			for (size_t j = 0; j < n; ++j)
				for (size_t i = 0; i < j; ++i)
					z[j] += operator[](i)*y[j-i];

			swap(z);

			return *this;
		}
		// x/y = z;
		// x = y*z;
		// x[j] = sum_{i=0}^j y[i]*z[j-i]
		number& operator/=(const number& y)
		{
			if (y.size() > size())
				resize(y.size());

			std::vector<X> z(n);
			for (size_t j = 0; j < n; ++j)
				for (size_t i = 0; i < j; ++i)
				z[j] += operator[](i)*y[j-i];

			swap(z);

			return *this;
		}
	};

} // dual

#ifdef _DEBUG
#include "../include/ensure.h"

template<class X, class Op>
inline void test_dual_number_op()
{
	dual::number<X> x{1,2,3}, y(x);

	ensure (y.size() == 3);
	y.op<Op>(4);
	for (size_t i = 0; i < x.size(); ++i)
		ensure (Op{}(x[i], 4) == y[i]);

	y = x;
	y.op<Op>(x);
	for (size_t i = 0; i < x.size(); ++i)
		ensure (Op{}(x[i], x[i]) == y[i]);

	//!!! test different sizes !!!
}

template<class X = double>
inline void test_dual_number()
{
	ensure (dual::detail::factorial<>(7) == 7*dual::detail::factorial<>(6));

	{
		dual::number<X> x(3);
		ensure (x.size() == 3);
		ensure (x[0] == 0);
		ensure (x[1] == 0);
		ensure (x[2] == 0);
	}

	test_dual_number_op<X, std::plus<X>>();
	test_dual_number_op<X, std::minus<X>>();
	test_dual_number_op<X, std::multiplies<X>>();
	test_dual_number_op<X, std::divides<X>>();
}

#endif // _DEBUG