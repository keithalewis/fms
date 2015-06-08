// xllprob.cpp - functions from prob
#define EXCEL12
#include "prob/normal.h"
#include "xll/xll.h"

using namespace prob;
using namespace xll;

static AddInX xai_normal_cdf(
	FunctionX(XLL_DOUBLEX XLL_DOUBLEX, _T("?xll_normal_cdf"), _T("PROB.NORMAL.CDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Category(_T("PROB"))
	.FunctionHelp(_T("Return the standard normal cumulative distribution function."))
	.Documentation()
);
double WINAPI xll_normal_cdf(double x)
{
#pragma XLLEXPORT
	double y{std::numeric_limits<double>::quiet_NaN()};

	try {
		y = normal<>::cdf(x);
		ensure (y==x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}