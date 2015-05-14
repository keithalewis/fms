// until.h - increment until a condition is met
#pragma once

namespace iter {

	template<class P, class I>
	inline I until(P p, I i)
	{
		while (!p(i))
			++i;

		return i;
	}

} // iter