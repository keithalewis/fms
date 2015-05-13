// until.h - increment until a condition is met
#pragma once

namespace iter {

	template<class P, class I>
	inline I until(I i, P p)
	{
		while (!p(i))
			++i;

		return i;
	}

} // iter