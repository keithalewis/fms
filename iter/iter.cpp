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

template<class T>
inline T expensive(T t)
{
	std::cout << "expensive(" << t << ")" << std::endl;

	return t;
}
inline void test_min_element()
{
	int a[] = {3,2,1,2,3};
	auto b = iter::min(fmap(expensive<int>,a));
	auto k = *b;
	k = *++b;
	k = *++b;
	k = *++b;
	k = *++b;
}

int main() 
{
	test_min_element();
//	coprime();
	try {
		test_accumulate();
		test_adjacent();
		test_apply();
		test_choose();
		test_concatenate();
		test_constant();
		test_elide();
		test_enumerator();
		test_enumerator_counted();
		test_enumerator_end();
		test_enumerator_null();
		test_enumerator_reverse();
		test_expr();
		test_factorial();
		test_fmap();
		test_iota();
		test_join();
		test_last();
		test_level();
		test_pick();
		test_pair();
		test_pow();
		test_skip();
		test_take();
		test_where();
		test_until();
		test_util();
		test_zigg();
	}
	catch (...) {
		return -1;
	}

	return 0;
}
