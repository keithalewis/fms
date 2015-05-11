# Iterator - input iterator classes

constexpr auto n_ = factorial{};
double e = sum(1/n_);
double x = 1;
double ex = sum(pow(x)/n_); // exp(x)

template<class I, T = input<I>::value_type>
double sum(input<I> i, std::function<bool(input<I> i, T)> p = [](input<I> i, T t) { return *i != 0 || *i + 1 != 1; })
{
	double s = 0;

	while (p(i,s))
		s += *i++;
}