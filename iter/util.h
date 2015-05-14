// util.h - utilites
#pragma once

// e.g., pick(_(2*n + 1), factorial{}, ) => (2n+1)!
#ifndef _
#define _(e) apply([](size_t n) { return e; })
#endif

namespace iter {

	template<class I>
	inline bool all(I i)
	{
		while (i)
			if (0 == *i++) return false;

		return true;
	}

	template<class I>
	inline bool any(I i)
	{
		while (i)
			if (0 != *i++) return true;

		return false;
	}

} // iter