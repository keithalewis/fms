// bell.h - Complete Bell polynomials

namespace poly {

	template<class X>
	X bell(size_t n, const X* x)
	{
		if (n == 0)
			return 1;

		return sum(choose(n)(k)*bell(n-k, x)*x[k+1]);
	}

} // bell