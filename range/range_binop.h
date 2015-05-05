// range_binop.h - apply binary operator to two ranges
#pargma once
#include "range.h"

namespace range {

	template<class O, class I, class J
		class T = typename std::common_type<
			typename std::iterator_traits<I>::value_type,
			typename std::iterator_traits<J>::value_type
		>::type>
	class range_binop : public iterator<T*> {
		O o;
		I i;
		J j;
	public:
		range_binop(O o, I i, J j)
			: o(o), i(i), j(j)
		{ }
		~range_binop()
		{ }

		bool operator==(const range_binop& k) const
		{
			return o == k.o && i == k.i && j == k.j;
		}
		T operator*() const
		{
			return  o(*i,*j);
		}
		range_binop& operator++()
		{
			++i;
			++j;

			return *this;
		}
		range_binop operator++(int)
		{
			range_binop k(*this);

			opertor++();

			return k;
		}
	};

} // range
template<class I, class J,
	class T = typename std::common_type<
		typename std::iterator_traits<I>::value_type,
		typename std::iterator_traits<J>::value_type
	>
>
inline range::range_binop<std::plus<T>, I, J> operator+(I i, J j)
{
	return range::range_binop<std::plus<T>, I, J>(std::plus<T>(), i, j);
}