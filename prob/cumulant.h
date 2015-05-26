// cumlant.h - various cumulants
#pragma once
#include "iter/iter.h"

namespace prob {
namespace cumulant {

	// cumulants for Esscher transformations
	template<class K, 
		class X = typename std::iterator_traits<K>::value_type>
	class esscher_ : public enumerator<K,X,std::input_iterator_tag> {
		constant_<X> s;
	public:
		using enumerator<K,X,std::input_iterator_tag>::i;

		esscher_()
		{ }
		esscher_(K k, const X& s)
			: enumerator<K,X,std::input_iterator_tag>(k), s(c(s))
		{ }

		// same operator bool() const
	
		// kappa_n^* = sum_{k>=0} kappa_{n+k} s^k/k!
		X operator*() const
		{
			// k = 0 plus k > 0
			return *i + sum0(ne(prod(skipn(1,i)*s/iota(X(1)))));
		}
		esscher_& operator++()
		{
			++i;

			return *this;
		}
		esscher_ operator++(int)
		{
			esscher_ e(*this);

			operator++();

			return e;
		}
	};
	// kappa_n^* = sum_{k>=0} kappa_{n+k} s^k/k!
	template<class K, class X = double>
	inline auto esscher(K kappa, const X& s)
	{
		return esscher_<K,X>(kappa, s);
	}

	template<class X = double>
	inline auto poisson(const X& mu)
	{
		return constant(mu);
	}
	template<class X = double, class S = double>
	inline auto poisson(const X& mu, const S& s)
	{
		return constant(mu*exp(s));
	}

	// (n-1)! mu^n
	template<class X = double>
	inline auto exponential(const X& mu)
	{
		return factorial<X>()*skipn(1, pow<X>(mu));
	}
	// (n-1)! mu^n (1/(1 - mu s)^{n-1} - 1)
	template<class X = double, class S = double>
	inline auto exponential(const X& mu, const S& s)
	{
		return factorial<X>()*skipn(1, pow<X>(mu));
	}

		
} // cumulant
} // prob
#ifdef _DEBUG
#include "include/ensure.h"

inline void test_cumulant()
{
	using namespace prob;
	using namespace cumulant;

	auto p = poisson(0.1);
	auto p_ = poisson(0.1,0.2);
	auto q = esscher(p, 0.2);

	double x = *p_;
	double y = *q;

	x = *++p_;
	y = *++q;

	x = *++p_;
	y = *++q;

	x = *++p_;
	y = *++q;

	x = *++p_;
	y = *++q;

}

#endif // _DEBUG
