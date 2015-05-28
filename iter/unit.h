// unit.h - promote single value to 1 item enumerater
#pragma once
#include <tuple>
#include "constant.h"
#include "enumerator/counted.h"

namespace iter {

	// t => {t}
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

	auto uu = unit(unit(1));
	auto v = *uu;
	ensure (*v == 1);
	ensure (!++v);
	ensure (!++uu);
}

#endif // _DEBUG