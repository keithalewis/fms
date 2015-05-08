// binop.h - input operators
#pragma once
#include <functional>
#include "apply.h"
#include "pair.h"

namespace iterator {

	template<class O, class I, class J,
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type>
	inline auto binop(O o, const iterator::input<I,T>& i, const iterator::input<J,U>& j)
	{
		return iterator::make_apply([o](const std::pair<T,U>& p) { return o(p.first, p.second); }, iterator::make_pair(i,j));
	}

} // iterator

template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type>
inline auto operator+(const iterator::input<I,T>& i, const iterator::input<J,U>& j)
{
	return iterator::binop(std::plus<std::common_type_t<T,U>>(), i, j);
}
/*
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type>
inline auto operator-(const iterator::input<I,T>& i, const iterator::input<J,U>& j)
{
	return iterator::binop(std::minus<std::common_type_t<T,U>>(), i, j);
}
	
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type>
inline auto operator*(const iterator::input<I,T>& i, const iterator::input<J,U>& j)
{
	return iterator::binop(std::multiplies<std::common_type_t<T,U>>(), i, j);
}
	
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type,
	class U = typename std::iterator_traits<J>::value_type>
inline auto operator/(const iterator::input<I,T>& i, const iterator::input<J,U>& j)
{
	return iterator::binop(std::divides<std::common_type_t<T,U>>(), i, j);
}
*/
#ifdef _DEBUG
#include <cassert>

using namespace iterator;

inline void test_binop()
{
	int i[] = {0,1,2};
	int j[] = {3,4,5};

	auto i_ = make_input(i);
	auto j_ = make_input(j);
	auto k = i_ + j_;
	assert (*k++ == 0 + 3);
	assert (*k == 1 + 4);
	assert (*++k == 2 + 5);

//	auto l = (i_ + i_*i_)/i_;
}

#endif //_DEBUG