// ftap.h - Fundamental Theorem of Asset Pricing
// price - X
// cash flow - C
// deflator - Pi
// X_j Pi_j = (C_{j+1} + X_{j+1}) Pi_{j+1}|A_j
// trade - Gamma
// position - Delta_j = sum_{i <= j} Gamma_i
// value - V_j = Delta_j . X_j
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>

namespace ftap {

	template<class Trade, class Time, class N = double>
	inline N position(Trade Gamma, Time t)
	{
		return sum0(until(t, Gamma));
	}

	template<class Position, class Price, class N = double>
	inline N value(Position Delta, Price X)
	{
		return sum0(Delta*X);
	}

} // ftap