// cumlant.h - various cumulants
#pragma once
#include "iter/iter.h"

namespace prob {
namespace cumulant {

	// cumulants for Esscher transformation
	template<class K, 
		class X = typename std::iterator_traits<K>::value_type>
	class esscher_ : public enumerator_<K,X,std::input_iterator_tag> {
		constant_<X> s;
	public:
		using enumerator_<K,X,std::input_iterator_tag>::i;

		esscher_()
		{ }
		esscher_(K k, const X& s)
			: enumerator_<K,X,std::input_iterator_tag>(k), s(c(s))
		{ }

		explicit operator bool() const
		{
			return true;
		}
	
		// kappa_n^* = sum_{k>=0} kappa_{n+k} s^k/k!
		X operator*() const
		{
			// k = 0 plus k > 0
			return sum0(ne(prod(skipn(1,i)*s/iota(X(1)))), *i);
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

	// reduced cumulants for Esscher transformation
	template<class K, 
		class X = typename std::iterator_traits<K>::value_type>
	class esscher_1_ : public enumerator_<K,X,std::input_iterator_tag> {
		constant_<X> s;
	public:
		using enumerator_<K,X,std::input_iterator_tag>::i;

		esscher_1_()
		{ }
		esscher_1_(K k, const X& s)
			: enumerator_<K,X,std::input_iterator_tag>(k), s(c(s))
		{ }

		explicit operator bool() const
		{
			return true;
		}
	
		// kappa_n^* = sum_{k>=0} (kappa_{n+k}/k!) s^k
		X operator*() const
		{
			// k = 0 plus k > 0
			return sum0(ne(prod(skipn(1,i)*s)), *i);
		}
		esscher_1_& operator++()
		{
			++i;

			return *this;
		}
		esscher_1_ operator++(int)
		{
			esscher_1_ e(*this);

			operator++();

			return e;
		}
	};
	template<class K, class X = double>
	inline auto esscher_1(K kappa, const X& s)
	{
		return esscher_1_<K,X>(kappa, s);
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
		return prod(concatenate(unit(1),iota(1))*c(mu));
	}
	// sum_{k>=0} (n+k-1)! s^k/k! = (n-1)!/(1 - s)^n
	template<class X = double, class S = double>
	inline auto exponential(const X& mu, const S& s)
	{
		return factorial<X>()*skipn(1, pow<X>(mu/(1 - s)));
		return prod(concatenate(unit(1),iota(1))*c(mu/(1 - s)));
	}

	// (n-1)! mu^n/n!
	template<class X = double>
	inline auto exponential_1(const X& mu)
	{
		return skipn(1, pow<X>(mu))/iota<X>(1);
	}
	// sum_{k>=0} (n+k-1)! s^k/k! = (n-1)!/(1 - s)^n n!
	template<class X = double, class S = double>
	inline auto exponential_1(const X& mu, const S& s)
	{
		return skipn(1, pow<X>(mu/(1 - s)))/iota<X>(1);
	}

} // cumulant
} // prob
#ifdef _DEBUG
#include "include/ensure.h"

inline void test_cumulant()
{
	using namespace prob;
	using namespace cumulant;


	{
		auto p = poisson(1.);
		auto p_ = poisson(1.,1.);
		auto q = esscher(p, 1.);

		for (int i = 0; i < 10; ++i)
			ensure (fabs(*p_++ - *q++) <= 2*std::numeric_limits<double>::epsilon());
	}
	{
		// diverges
		/*
		auto p = exponential(1.);
		auto p_ = exponential(1.,.01);
		auto q = esscher(p, .01);
		*/
		auto p = exponential_1(1.);
		auto p_ = exponential_1(1.,.01);
		auto q = esscher_1(p, .01);

		auto b = skipn(10, buffer(0, p_ - q));
		// lousy convergence
		std::function<double(const double&)> fabs_ = [](const double& x) { return fabs(x); };
		ensure (back(max(take(10,fmap(fabs_, p_ - q)))) < 0.01);
	}
}

#endif // _DEBUG
