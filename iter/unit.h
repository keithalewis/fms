// unit.h - promote single value to 1 item enumerater
#pragma once
#include "constant.h"
#include "enumerator/counted.h"

namespace iter {

	template<class T>
	inline auto unit(const T& t)
	{
		return ce(c(t),1);
	}

}
