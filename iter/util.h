// util.h - utilites
#pragma once

// e.g., pick(_(n, 2*n + 1), factorial{}, ) => (2n+1)!
// lambda macro
#ifndef _
#define _(x,...) [](auto x) { return (__VA_ARGS__) ; }
#endif

namespace iter {

	template<class I>
	inline bool all(I i)
	{
		while (i)
			if (0 == *i++) 
				return false;

		return true;
	}

	template<class I>
	inline bool any(I i)
	{
		while (i)
			if (0 != *i++) 
				return true;

		return false;
	}

} // iter