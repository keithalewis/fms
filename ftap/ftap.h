// ftap.h - Fundamental Theorem of Asset Pricing
// price - X
// cash flow - C
// deflator - Pi
// X_j Pi_j = (C_{j+1} + X_{j+1}) Pi_{j+1}|A_j
// trade - Gamma
// position - Delta_j = sum_{i <= j} Gamma_i
// value - V_j = Delta_j . X_j
// V_j Pi_j = (A_{j+1} + V_{j+1})Pi_{j+1}|A_j
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>

namespace ftap {

	// instrument is a time,amount enumerator<T,A>
	template<class T, class C>
	struct cash_flow {
		T t;
		C c;
	};

	template<class T, class O, class R>
	struct european {
		std::function<R(O)> f;
		T t;
		bool expired;
		european(std::function<R(O)> f, T t)
			: f(f), t(t), expired(false)
		{ }
		operator bool() const
		{
			return !expired;
		}
		R operator()(O o)
		{
			return expired ? 0 : f(o);
		}
		european& operator++()
		{
			expired = true;
		}
	};

	// value is a function
	inline V value(I i, Pi pi)
	{
		return [=i](auto p) {
			i ? sum0(map(value, atoms(++i))) : 0;
		};
	}

	template<class Trade>
	inline auto position(Trade gamma)
	{
		return sum(Gamma);
	}

	template<class Position, class Price, class N = double>
	inline N value(Position Delta, Price X)
	{
		return sum0(Delta*X);
	}

} // ftap