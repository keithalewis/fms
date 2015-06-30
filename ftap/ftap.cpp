// ftap.cpp - test ftap functions
#include <iostream>
#include <cmath>
#include <utility>
#include "binomial.h"

struct bond {
	double R;
	bond(double R) 
		: R(R) 
	{ }
	double operator()(int j, int w) const
	{
		return pow(R,j);
	}
};
struct stock {
	double R, s;
	stock(double R, double s) 
		: R(R), s(s) 
	{ }
	double operator()(int j, int w) const
	{
		// ensure w in {-j, -j + 2, ..., j}
		return pow(R*cosh(s*w), j);
	}
};

template<class Stock>
struct option {
	int t; // expiration
	double k; // strike
	Stock S;
	option(int t, double k, Stock S)
		: t(t), k(k), S(S)
	{ }
	double operator()(int j, int o) const
	{
		return j == t ? std::max(S(j, o) - k, 0.) : 0;
	}
};

inline double Pi(int j, int w)
{
	ensure (-j <= w && w <= j);
	ensure ((j - w)%2 == 0);

	double pi = 1;
	for (int i = 0; i < j; ++i) {
		pi *= (j - i);
		pi /= (i + 1);
	}

	return pi*pow(2.,-j);
}

// value(i,w) = V_i*Pi_i(w)
template<class Stock>
inline std::function<double(int,int)> value(const option<Stock>& o)
{
	return [o](int i, int w) -> double { 
		return i == o.t 
			? o(i, w)*Pi(i,w)
			: value(o)(i + 1, w + 1) + value(o)(i + 1, w - 1);
	};
}

int main(void)
{
	try {
		{
			option<stock> o(3, 0, stock(1, .1));
			auto v = value(o);
			ensure (v(3,-3) == o(3,-3)*Pi(3,-3));
			ensure (v(3,-1) == o(3,-1)*Pi(3,-1));
			ensure (v(3,1) == o(3,1)*Pi(3,1));
			ensure (v(3,3) == o(3,3)*Pi(3,3));

			double v0 = (o(3,-3) + 3*o(3,-1) + 3*o(3,1) + o(3,3))/8;
			double v1 = v(0,0);
			ensure (v0 == v1);
		}
		{
			option<stock> o(3, 1, stock(1, .1));
			auto v = value(o);
			ensure (v(3,-3) == o(3,-3)*Pi(3,-3));
			ensure (v(3,-1) == o(3,-1)*Pi(3,-1));
			ensure (v(3,1) == o(3,1)*Pi(3,1));
			ensure (v(3,3) == o(3,3)*Pi(3,3));

			double v0 = (o(3,-3) + 3*o(3,-1) + 3*o(3,1) + o(3,3))/8;
			double v1 = v(0,0);
			ensure (v0 == v1);
		}

		test_binomial();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}