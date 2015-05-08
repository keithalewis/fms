// iterator.h
#pragma once
#include <stdexcept>
#include "enumerator.h"
#include "apply.h"
#include "binop.h"
#include "pair.h"
/*
#include "constant.h"
#include "factorial.h"
#include "skip.h"
#include "concatenate.h"
#include "sequence.h"

*/
/*
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type>
inline auto operator+(const iterator::input<I,T>& i, const iterator::input<J,U>& j)
{
	return iterator::make_apply([](const std::pair<T,U>& p) { return p.first + p.second; }, iterator::make_pair(i,j));
}

#ifdef _DEBUG
#include <cassert>

using namespace iterator;

inline void test_ops()
{
	int a[] = {0,1,2};
	int b[] = {3,4,5};

	{
		auto plus = [](const std::pair<int,int>& ij) { return ij.first + ij.second; };
		auto ab_ = make_pair(a,b);
		auto ab = make_apply(plus, ab_);
		assert (*ab == a[0]+b[0]);
		assert (*++ab == a[1]+b[1]);
		ab++;
		assert (*ab == a[2]+b[2]);
	}
	{
		auto a_ = make_input(a);
		auto b_ = make_input(b);
		auto ab = a_ + b_;
		assert (*ab == a[0]+b[0]);
	}

}
#endif // _DEBUG
*/
