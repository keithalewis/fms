// expr.h - iter expressions
#pragma once
#include <functional>
#include "constant.h"

namespace iter {

	template<class O, class I, class J, class T, class U, class V>
	class binop : public input_base<std::pair<I,J>,V> {
		O o;
		std::pair<I,J> ij;
	public:
		typedef V value_type;
		binop(O o, I i, J j)
			: o(o), ij(std::make_pair(i, j))
		{ }
/*		binop(const binop&) = default;
		binop(binop&&) = default;
		binop& operator=(const binop&) = default;
		binop& operator=(binop&&) = default;
		~binop()
		{ }
*/
		operator std::pair<I,J>() const
		{
			return ij;
		}
		operator bool() const
		{
			return ij.first && ij.second;
		}
		V operator*() const
		{
			return o(*ij.first, *ij.second);
		}
		binop& operator++()
		{
			++ij.first;
			++ij.second;

			return *this;
		}
		binop operator++(int)
		{
			binop a(*this);

			operator++();

			return a;
		}
	};
	template<class O, class I, class J, 
		class T = typename std::iterator_traits<I>::value_type, 
		class U = typename std::iterator_traits<J>::value_type,
		class V = std::common_type_t<T,U>>
	inline binop<O,I,J,T,U,V> make_binop(O o, I i, J j)
	{
		return binop<O,I,J,T,U,V>(o, i, j);
	}

	template<class I, class J, class T, class U, class V>
	struct add : public binop<std::plus<V>,I,J,T,U,V> {
//		using binop<std::plus<V>,I,J,T,U,V>::binop;
		add()
		{ }
		add(I i, J j)
			: binop<std::plus<V>,I,J,T,U,V>(std::plus<V>{}, i, j)
		{ }
	};
	template<class I, class J, 
		class T = typename std::iterator_traits<I>::value_type, 
		class U = typename std::iterator_traits<J>::value_type,
		class V = std::common_type_t<T,U>>
	inline auto make_add(I i, J j)
	{
		return add<I,J,T,U,V>(i, j);
	}


	template<class I, class J, class T, class U, class V>
	struct sub : public binop<std::minus<V>,I,J,T,U,V> {
//		using binop<std::minus<V>,I,J,T,U,V>::binop;
		sub()
		{ }
		sub(I i, J j)
			: binop<std::minus<V>,I,J,T,U,V>(std::minus<V>{}, i, j)
		{ }
	};

	template<class I, class J, 
		class T = typename std::iterator_traits<I>::value_type, 
		class U = typename std::iterator_traits<J>::value_type,
		class V = std::common_type_t<T,U>>
	inline auto make_sub(I i, J j)
	{
		return sub<I,J,T,U,V>(i, j);
	}

	template<class I, class J, class T, class U, class V>
	struct mul : public binop<std::multiplies<V>,I,J,T,U,V> {
//		using binop<std::multiplies<V>,I,J,T,U,V>::binop;
		mul()
		{ }
		mul(I i, J j)
			: binop<std::multiplies<V>,I,J,T,U,V>(std::multiplies<V>{}, i, j)
		{ }
	};
	template<class I, class J, 
		class T = typename std::iterator_traits<I>::value_type, 
		class U = typename std::iterator_traits<J>::value_type,
		class V = std::common_type_t<T,U>>
	inline auto make_mul(I i, J j)
	{
		return mul<I,J,T,U,V>(i, j);
	}

		template<class I, class J, class T, class U, class V>
	struct div : public binop<std::divides<V>,I,J,T,U,V> {
//		using binop<std::divides<V>,I,J,T,U,V>::binop;
		div()
		{ }
		div(I i, J j)
			: binop<std::divides<V>,I,J,T,U,V>(std::divides<V>{}, i, j)
		{ }
	};
	template<class I, class J, 
		class T = typename std::iterator_traits<I>::value_type, 
		class U = typename std::iterator_traits<J>::value_type,
		class V = std::common_type_t<T,U>>
	inline auto make_div(I i, J j)
	{
		return div<I,J,T,U,V>(i, j);
	}
} // iter

template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type, 
	class U = typename std::iterator_traits<J>::value_type,
	class V = std::common_type_t<T,U>>
inline iter::add<I,J,T,U,V> operator+(I i, J j)
{
	return iter::add<I,J,T,U,V>(i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type, 
	class U = typename std::iterator_traits<J>::value_type,
	class V = std::common_type_t<T,U>>
inline iter::sub<I,J,T,U,V> operator-(I i, J j)
{
	return make_sub(i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type, 
	class U = typename std::iterator_traits<J>::value_type,
	class V = std::common_type_t<T,U>>
inline iter::mul<I,J,T,U,V> operator*(I i, J j)
{
	return make_mul(i, j);
}
template<class I, class J,
	class T = typename std::iterator_traits<I>::value_type, 
	class U = typename std::iterator_traits<J>::value_type,
	class V = std::common_type_t<T,U>>
inline iter::div<I,J,T,U,V> operator/(I i, J j)
{
	return make_div(i, j);
}

#ifdef _DEBUG
#include <cassert>

using namespace iter;

template<class T, class U, template<typename TU> class O>
inline void test_expr_binop()
{
	O<std::common_type_t<T,U>> o{};
	T a[] = {1,2,3};
	U b[] = {4,5,6};

	auto ab = make_binop(o, a, b);
	int i = 0;
	assert (*ab == o(a[i],b[i]));
	ab++; i++;
	assert (*ab == o(a[i],b[i]));
	++i;
	assert (*++ab == o(a[i],b[i]));
}

inline void test_expr()
{
	test_expr_binop<int,int,std::plus>();
	test_expr_binop<int,double,std::plus>();
	test_expr_binop<double,int,std::plus>();
	test_expr_binop<double,double,std::plus>();

	test_expr_binop<int,int,std::minus>();
	test_expr_binop<int,double,std::minus>();
	test_expr_binop<double,int,std::minus>();
	test_expr_binop<double,double,std::minus>();

	test_expr_binop<int,int,std::multiplies>();
	test_expr_binop<int,double,std::multiplies>();
	test_expr_binop<double,int,std::multiplies>();
	test_expr_binop<double,double,std::multiplies>();

	test_expr_binop<int,int,std::divides>();
	test_expr_binop<int,double,std::divides>();
	test_expr_binop<double,int,std::divides>();
	test_expr_binop<double,double,std::divides>();

	int a[] = {1,2,3};

	{
		auto aa_ = make_add(make_input(a),make_input(a));
		auto aa = make_add(a,a);
		assert (*aa == 1 + 1);
		assert (*++aa == 2 + 2);
		aa++;
		assert (*aa == 3 + 3);

		auto a1 = make_add(make_input(a), make_input(a));
		auto aaa = make_add(make_add(make_input(a),make_input(a)), make_input(a));
		assert (*aaa == 3);
		assert (*++aaa == 6);
		aaa++;
		assert (*aaa == 9);

		auto a4 = make_add(a,a) + make_input(a);
		assert (*a4 == 3);
		assert (*++a4 == 6);
		a4++;
		assert (*a4 == 9);

		auto ai = make_input(a);
		auto a5 = (ai + ai) + (ai + ai) + ai;
		int i = 0;
		assert (*a5 == 5*a[i]);
		assert (*++a5 == 5*a[++i]);
		a5++;
		assert (*a5 == 5*a[++i]);
		{
			auto a6 = make_input(a) + c(1);// constant<int>(1);
			assert (*a6 == a[i=0] + 1);
			assert (*++a6 == a[++i] + 1);
			a6++; i++;
			assert (*a6 == a[i] + 1);
		}
		{
			auto a6 = constant<int>(1) + make_input(a);
			assert (*a6 == a[i=0] + 1);
			assert (*++a6 == a[++i] + 1);
			a6++; i++;
			assert (*a6 == a[i] + 1);
		}
	}
	{
		auto aa = make_mul(make_input(a),make_input(a));
		assert (*aa == 1 * 1);
		assert (*++aa == 2 * 2);
		aa++;
		assert (*aa == 3 * 3);

		auto a1 = make_mul(make_input(a), make_input(a));
		auto aaa = make_mul(make_mul(make_input(a),make_input(a)), make_input(a));
		assert (*aaa == 1);
		assert (*++aaa == 8);
		aaa++;
		assert (*aaa == 27);

		auto a4 = make_mul(a,a) * make_input(a);
		assert (*a4 == 1);
		assert (*++a4 == 8);
		a4++;
		assert (*a4 == 27);
	}
}
#endif // _DEBUG
