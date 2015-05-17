// iter.cpp
#include "include/ensure.h"
#include "iter.h"

using namespace iter;

template<class I, class T>
struct en : public std::iterator<typename std::iterator_traits<I>::iterator_category, T> {
	I i;
	en()
	{ }
	en(I i)
		: i(i)
	{ }
	operator bool() const
	{
		return true;
	}
};
template<class I, class T>
struct cen : public en<I,T> {
	size_t n;
	I i;
	cen()
	{ }
	cen(I i, size_t n)
		: i(i), n(n)
	{ }
	operator bool() const
	{
		return n != 0;
	}
};

int main() 
{
	en<int*,int> i;
	cen<int*,int> ci;
	bool b;
	if (i)
		b = true;
	if (ci)
		b = false;

	try {
		test_accumulate();
		test_adjacent();
		test_apply();
		test_choose();
		test_concatenate();
		test_constant();
		test_enumerator();
		test_enumerator_counted();
		test_enumerator_end();
		test_enumerator_null();
		test_enumerator_reverse();
		test_expr();
		test_factorial();
		test_fmap();
		test_iterator();
		test_iota();
		test_last();
		test_level();
		test_pick();
		test_pair();
		test_pow();
		test_skip();
		test_take();
		test_where();

	}
	catch (...) {
		return -1;
	}

	return 0;
}
