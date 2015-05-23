// unit.h - promote single value to 1 item enumerater
#pragma once
#include <tuple>
#include "constant.h"
#include "enumerator/counted.h"

namespace iter {
/*
	// {e0, e1, ...} => {{e0}, {e1}, ...}
	template<class... I, class... T>
	class unit_ : public enumerator<std::tuple<I>, std::tuple<T>, std::input_iterator_tag> {
	public:
		unit_()
		{ }
		unit_(I... is)
			: enumerator<std::tuple<I>>(std::make_tuple(is))
		{ }
	};
*/
	template<class T>
	inline auto unit(const T& t)
	{
		return ce(c(t),1);
	}

}
#ifdef _DEBUG
#include "include/ensure.h"

inline void test_unit()
{
	auto u = unit(1);
	ensure (u);
	ensure (*u == 1);
	ensure (!++u);
}

#endif // _DEBUG