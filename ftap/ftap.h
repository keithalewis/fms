// ftap.h - Fundamental Theorem of Asset Pricing
// X_j Pi_j = (C_{j+1} + X_{j+1}) Pi_{j+1}|A_j
// V_j = Delta_j . X_j, Delta_j = sum_{i <= j} Gamma_i
#pragma once
#include <algorithm>
#include <functional>
#include <numeric>

namespace ftap {

	// pair of iterators
	template<class I>
	using range = std::pair<I,I>;

	template<class I>
	inline /* std::enable_if .. ::type */ range<I> make_range(I b, I e)
	{
		return std::make_pair<I,I>(b, e);
	}

	template<class I>
	inline I begin(range<I> r) { return r.first; }
	template<class I>
	inline I end(range<I> r) { return r.second; }

	template<class I, class F>
	inline F for_each(range<I> r, F f) { return std::for_each(begin(r), end(r), f); }

	template<class I>
	class range_iterator {

	};

	template<class Atom>
	struct algebra {
		typedef Atom atom_type;
	};

	template<class Price, class CashFlow, class Measure>
	struct model {
		const Price& X;
		const CashFlow& C;
		const Measure& Pi;
		model(const Price& X, const CashFlow& C, const Measure& Pi)
			: X(X), C(C), Pi(Pi)
		{ }
	};

	template<class Positions, class Prices>
	inline value(Positions delta, Prices x) -> std::function<
	{
		return std::inner_product(std::begin(delta), std::end(delta), std::begin(x), 0);
	}
/*
	template<class Model>
	std::function<R(typename Measure::atoms)> value(Price X, CashFlow C, Measure Pi)
	{
		return [X,C,Pi](typename Measure::atoms a) {

		}
	}
*/
} // ftap