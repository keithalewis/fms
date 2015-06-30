// binomial.h - the binomial model
// Random walk
// Let Omega = {-1,1}^oo and W_j(w) = w_1 + ... + w_j.
// Define initial segment {w}_k = {w' in Omega : w'_j = w_j for j <= k} so P({w}_k) = 1/2^k.
// Partition P_k = {{w}_k : w in Omega } has 2^k atoms
// Partition L_k = {{W_k = l} : l = -k, -k + 2, ..., k} has k atoms
// Atom of P_k -> subatoms in P_{k+1}
// Atom A of L_k -> Pi(A)
// Omega -> atoms of P_1
#include <iterator>

/*
Pi takes any subset of Omega.
Functions are defined on atoms.

v(i,A,C,Pi,w)
{
	return sum0(apply([](x) { return (C(x) + A(x))*Pi(x); }, atoms(i+1, w)));
}
	

v(A a, Pi pi, S s = 0)
{
	for (b : atoms(a)) {
		s += v(b,pi);
	}

	return s;
}
*/

// enumerator: iterator with operator bool() returning false when done
// sum an enumerator, from 0 by default
template<class E, class S>
inline S sum0(E e, S s = 0)
{
	while (e) {
		s += *e;
		++e;
	}

	return s;
}

struct sequence : public std::iterator<std::input_iterator_tag, int> {
	int i, di, n;
	sequence(int i = 0, int di = 1, int n = 1)
		: i(i), di(di), n(n)
	{ }
	// current level
/*	operator int() const
	{
		return i;
	}
*/	bool operator==(const sequence& s) const
	{
		return i == s.i && di == s.di && n == s.n;
	}
	bool operator!=(const sequence& s) const
	{
		return n != 0;
	}
	sequence begin() const
	{
		return *this;
	}
	sequence end() const
	{
		return sequence(0, 0, -1);
	}

	explicit operator bool() const
	{
		return n != 0;
	}
	int operator*() const
	{
		return i;
	}
	sequence& operator++()
	{
		if (n) {
			--n;
			i += di;
		}

		return *this;
	}
	sequence operator++(int)
	{
		sequence s(*this);

		operator++();

		return s;
	}
};

// -n, -n + 2, ..., n
template<int N>
struct L : public sequence {
	using sequence::sequence;
//	using sequence::operator int;
	using sequence::operator bool;
	using sequence::operator++;

	L()
		: sequence(-N, 2, N + 1)
	{ }
	int size() const
	{
		return N;
	}
};
template<int N>
inline L<N+1> next(const L<N>& l)
{
	return L<N+1>{};
}
template<int N>
inline auto atoms(const L<N>& l)
{
	return sequence(*l - 1, 2, 2);
}
/*
f(W_n)Pi_n(L<0>)
f(W_n)Pi_n(atoms(L<0>))
sum_atoms(L<0>) f(W_n)Pi_n(a1)
...
f(W_n)(an)
f(W_n(an))
Note: Pi is fixed
*/
/*
template<class F, class A>
inline double v(F f, A a)
{
	double s{0};

	for (auto b : atoms(a)) {
		s += v(f,b);
	}

	return s;
}
template<class F, class A>
inline typename std::enable_if<std::is_same<A,L<2>>::value,double>::type v(F f, A a)
{
	return f(a);
}
*/
#ifdef _DEBUG
#include <array>
#include <cmath>
#include <functional>
#include "include/ensure.h"

inline void test_binomial()
{
	/*
	double w;
	w = v([](double x) { return x > 0 ? x : 0; }, L<0>{});
	{
		sequence s;
//		ensure (s == 0);
		ensure (*s == 0);
		ensure (s);
		++s;
		ensure (!s);
	}
	{
		sequence s2(2, 1, 2);
		ensure (*s2 == 2);
		ensure (*++s2 == 3);
		s2++;
		ensure (!s2);
	}
	{
		L<2> l2;
		ensure (l2.size() == 2);
		ensure (*l2 == -2);
		ensure (*++l2 == 0);
		l2++;
		ensure (*l2 == 2);
		ensure (!++l2);

		auto l3 = next(l2);
		ensure (l3.size() == 3);
		ensure (*++l3 == -1);
		auto a = atoms(l3);
		ensure (*a == -2);
		ensure (*++a == 0);
		ensure (!++a);
	}
	{
		ensure (sum0(L<3>{},0) == 0);
	}
	{
		L<4> l4;
		int i = -4;
		for (auto l : l4) {
			ensure (l == i);
			i += 2;
		}
	}
	*/
}

#endif // _DEBUG