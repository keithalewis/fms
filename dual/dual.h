// dual.h - dual numbers for computing machine precision derivatives
#pragma once
#include <algorithm>
#include <functional>
#include <valarray>

namespace dual {

	template<class X, size_t N = 0>
	struct number : public std::valarray<X> {
		size_t n = N;
		using std::valarray<X>::valarray;
		using std::valarray<X>::size;
		using std::valarray<X>::swap;
		using std::valarray<X>::operator[];
		using std::valarray<X>::operator+=;
		using std::valarray<X>::operator-=;
		using std::valarray<X>::operator*=;
		using std::valarray<X>::operator/=;

		number()
		{ }
		// x0 + 0 J + 0 J^2 + ... + 0 J^{n-1}
		number(size_t n, const X& x)
			: std::valarray<X>(n)
		{
			if (n > 0)
				operator[](0) = x;
		}
		number(const std::valarray<X>& y)
			: std::valarray<X>(y), n(y.size())
		{ }
		number(std::valarray<X>&& y)
			: std::valarray<X>(std::move(y)), n(y.size())
		{ }
		number& operator=(const std::valarray<X>& y)
		{
			std::valarray<X>::operator=(y);
			n = y.size();

			return *this;
		}
		number& operator=(std::valarray<X>&& y)
		{
			std::valarray<X>::operator=(std::move(y));
			n = y.size();

			return *this;
		}
		~number()
		{ }

		bool operator==(const valarray<X>& y) const
		{
			return std::equal(std::begin(*this), std::end(*this), std::begin(y), std::end(y));
		}
		bool operator!=(const valarray<X>& y) const
		{
			return !operator==(y);
		}

		void swap(number& y)
		{
			std::valarray<X>::swap(y);
			std::swap(n, y.n);
		}

		// i-th derivative
		X operator()(size_t i) const
		{
			X x = operator[](i);

			while (i > 1)
				x /= i--;

			return x;
		}

		// vector operations
		// (x*y)[k] = sum_{i+j=k}^j x[i]*y[j]
		number& operator*=(const number& y)
		{
			std::valarray<X> z(X(0), n ? n : size() + y.size() - 1);

			for (size_t i = 0; i < size(); ++i) {
				for (size_t j = 0; j < y.size(); ++j)
					if (i + j < z.size())
						z[i + j] += operator[](i)*y[j];
			}

			n = z.size();
			swap(z);

			return *this;
		}
		// x/y = z;
		// x = y*z;
		// xi = sum_{j+k=i} yj*zk
		// x0 = y0 z0
		// z0 = x0/y0
		// x1 = y0 z1 + y1 z0;
		// z1 = (x1 - y1 z0)/y0
		// x2 = y0 z2 + y1 z1 + y2 z0
		// z2 = (x2 - y1 z1 - y2 z0)/y0
		number& operator/=(const number& y)
		{
			// same size as this
			std::valarray<X> z(X(0), size());

			if (size())
				z[0] = operator[](0)/y[0];

			for (size_t i = 1; i < size(); ++i) {
				z[i] = operator[](i);
				for (size_t j = 1; j <= i && j < y.size(); ++j) {
					z[i] -= y[j]*z[i - j];
				}
				z[i] /= y[0];
			}

			swap(z);

			return *this;
		}
	};

} // dual

template<class X, size_t Nx, size_t Ny>
dual::number<X> operator*(const dual::number<X,Nx>& x, const dual::number<X,Ny>& y)
{
	dual::number<X> z{x};

	z *= y;

	return z;
}
template<class X, size_t Nx, size_t Ny>
dual::number<X> operator/(const dual::number<X,Nx>& x, const dual::number<X,Ny>& y)
{
	dual::number<X> z{x};

	z /= y;

	return z;
}

#ifdef _DEBUG
#include "../include/ensure.h"


template<class X = double>
inline void test_dual_number()
{
	{
		dual::number<X> x(3, 1.23);
		dual::number<X> x2{x};
		ensure (x2 == x);
		x = x2;
		ensure (x == x2);

		ensure (x.size() == 3);
		ensure (x[0] == 1.23);
		ensure (x[1] == 0);
		ensure (x[2] == 0);

		x += 1;
		ensure (x[0] == 1.23 + 1);
		ensure (x[1] == 1);
		ensure (x[2] == 1);
		x -= 2;
		x *= 3;
		x /= 4;
		ensure (x[0] = (1.23 - 1)*3/4);
	}
	{
		dual::number<X> x{1,2}, y{3,4};
		dual::number<X> z;
		z = x + y;
		ensure (z[0] = x[0] + y[0]);
		ensure (z[1] = x[1] + y[1]);

		z = x * y;
		ensure (z.size() == 3);
		ensure (z[0] == 1*3);
		ensure (z[1] == 1*4 + 2*3);
		ensure (z[2] == 2*4);

		z /= y;
		auto zi = std::valarray<X>(z[std::slice(0,2,1)]);
		ensure (x == zi);
	}
}

#endif // _DEBUG