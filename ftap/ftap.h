// ftap.h - Fundamental Theorem of Asset Pricing
// price - X
// cash flow - C
// deflator - Pi
// X_j Pi_j = (C_{j+1} + X_{j+1}) Pi_{j+1}|A_j
// trade - Gamma
// position - Delta_j = sum_{i <= j} Gamma_i
// value - V_j = Delta_j . X_j
// V_j Pi_j = (A_{j+1} + V_{j+1})Pi_{j+1}|A_j
/*
value: (T, A, Pi) -> (O -> R)
value(j, a, pi) {
	if (a) {
		return [j,pi](O o) {
			R s = 0;
			for (a_ : atoms(j+1,a)) {
				s += (a_ + value(j+1,a_,pi)*pi(a_);
			}
			return s;
		};
	}
	else {
		return [](O) { return 0; };
	}
}
*/
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

	// Time, Omega, Result
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
		cash_flow<T,R> operator()(O o)
		{
			return expired ? cash_flow{T(0),R(0)} : cash_flow{t,f(o)};
		}
		european& operator++()
		{
			expired = true;

			return *this;
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