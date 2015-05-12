// sum.h - add input an enumerations
#pragma once
#include <iterator>

namespace iter {

	// sum an enumerator
	template<class E, class T = typename std::iterator_traits<E>::value_type>
	inline T sum(E e)
	{
		T s{0};

		while (e)
			s += *e++;

		return s;
	}

} // iter