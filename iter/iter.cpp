// iter.cpp
#include <iostream>
#include "include/ensure.h"
#include "iter.h"

using namespace iter;

/*

template<class y, class... x>
struct Y { 
	using f = std::function<y(x...)>;
	using ff  = std::function<y(f<y,x...>, x...)>;
	
	ff<y,x...> g;
	y operator()(x... xs) const
	{
		return f<y,x...>(*this, xs...);
	}
	Y(ff<y,x...> h)
		: g(h)
	{ }
};

inline int gcd(int a, int b)
{
	if (b == 0)
		return a;
	if (a < b)
		return gcd(b, a);

	return gcd(a%b, b);
}

#include "util.h"

void coprime()
{
//	auto co = [](auto p) { return 1 == gcd((*p).first,(*p).second); };
	auto l = [](int n) { return level(n); };
	auto w = where(_(p, 1 == gcd((*p).first,(*p).second)), join(fmap(l, iota(2))));
	auto x = *w;
	}
*/


template<class I>
inline auto next_prime(I i)
{
	auto p = *i;

	return concatenate(unit(p), where([p](I i) { return *i % p != 0; }, ++i));
}

int main() 
{
	/*
	auto p2 = next_prime(iota(2));
	ensure (2 == *p2);
	auto p3 = next_prime(++p2);
	ensure (3 == *p3);
	auto p5 = next_prime(++p3);
	ensure (5 == *p5);
	auto p7 = next_prime(++p5);
	ensure (7 == *p7);
	auto p11 = next_prime(++p7);
	ensure (11 == *p11);
	*/
	try {
		test_enumerator();
		test_enumerator_counted();
		test_enumerator_end();
		test_enumerator_null();
		test_enumerator_reverse();
		test_accumulate();
		test_pair();
		test_expr();
		test_adjacent();
		test_apply();
		test_buffer();
		test_choose();
		test_concatenate();
		test_constant();
		test_cycle();
		test_elide();
		test_factorial();
		test_fmap();
		test_iota();
		test_join();
		test_last();
		test_level();
		test_pick();
		test_pow();
		test_skip();
		test_take();
		test_unit();
		test_until();
		test_util();
		test_where();
		test_zigg();
		/*
		test_bind();
*/	}
	catch (...) {
		return -1;
	}

	return 0;
}
