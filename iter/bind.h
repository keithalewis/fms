// bind.h - monadic bind
#pragma once
#include <functional>
#include "enumerator.h"

namespace iter {

	// I t -> (t -> J u) -> J u
	template<class F, class I, class J, 
		class T = typename std::iterator_traits<I>::value_type,
		class U = typename std::iterator_traits<J>::value_type
	>
	class bind_ : public enumerator<J,U,std::input_iterator_tag> {
		std::function<J(T)> f;
		I i;
	public:
		bind_()
		{ }
		bind_(F f, I i)
			: f(f), i(i)
		{ }

		operator bool() const
		{
			return i;
		}
		U operator*()
		{
			return *f(*i);
		}
		bind_& operator++()
		{
			++i;

			return *this;
		}
		bind_ operator++(int)
		{
			bind_ b(*this);

			operator++();

			return b;
		}
	};

} // iter
#ifdef _DEBUG
#include "include/ensure.h"
#include "concatenate.h"
#include "iota.h"
#include "unit.h"
#include "where.h"


inline void test_bind()
{
	auto a = iota(2);
	auto b = concatenate(unit(*a), where([a](auto i) { return *i % *a != 0; }, ++a));
	auto c = *b;
	ensure (c == 2);
	c = *++b;
	c = *++b;
	c = *++b;
	c = *++b;
	c = *++b;
}

#endif // _DEBUG