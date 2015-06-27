// xllprob.cpp - functions from prob
#define EXCEL12
#include "prob/normal.h"
#include "xll/xll.h"

using namespace prob;
using namespace xll;

static AddInX xai_normal_cdf(
	FunctionX(XLL_DOUBLEX XLL_DOUBLEX, _T("?xll_prob_normal_cdf"), _T("PROB.NORMAL.CDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Category(_T("PROB"))
	.FunctionHelp(_T("Return the standard normal cumulative distribution."))
	.Documentation(R_(
		The standard normal density is <math>exp(-x<sup>2</sup>/2)/sqrt 2pi</math>.
	))
);
double WINAPI xll_prob_normal_cdf(double x)
{
#pragma XLLEXPORT
	doublex y;

	try {
		y = normal<>::cdf(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}
static AddInX xai_normal_cdf_bell(
	FunctionX(XLL_DOUBLEX XLL_DOUBLEX, _T("?xll_prob_normal_cdf_bell"), _T("PROB.NORMAL.CDF.BELL"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the value at which to calculate the cumulative distribution function."))
	.Category(_T("PROB"))
	.FunctionHelp(_T("Return the standard normal cumulative distribution."))
	.Documentation(R_(
	The standard normal density is <math>exp(-x<sup>2</sup>/2)/sqrt 2pi</math>.
	))
	);
double WINAPI xll_prob_normal_cdf_bell(double x)
{
#pragma XLLEXPORT
	doublex y;

	try {
		y = std_normal<double,bell_impl>::cdf(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}
static AddInX xai_normal_inv_bell(
	FunctionX(XLL_DOUBLEX XLL_DOUBLEX, _T("?xll_prob_normal_inv_bell"), _T("PROB.NORMAL.INV.BELL"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the value at which to calculate the inverse cumulative distribution function."))
	.Category(_T("PROB"))
	.FunctionHelp(_T("Return the standard normal cumulative distribution."))
	.Documentation(R_(
	The standard normal density is <math>exp(-x<sup>2</sup>/2)/sqrt 2pi</math>.
	))
	);
double WINAPI xll_prob_normal_inv_bell(double x)
{
#pragma XLLEXPORT
	doublex y;

	try {
		y = std_normal<double,bell_impl>::inv(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}

static AddInX xai_normal_pdf(
	FunctionX(XLL_DOUBLEX XLL_DOUBLEX, _T("?xll_prob_normal_pdf"), _T("PROB.NORMAL.PDF"))
	.Arg(XLL_DOUBLEX, _T("x"), _T("is the value at which to calculate the density function."))
	.Category(_T("PROB"))
	.FunctionHelp(_T("Return the standard normal density."))
	.Documentation(R_(
	The standard normal density is <math>exp(-x<sup>2< / sup> / 2) / sqrt 2pi< / math>.
	))
	);
double WINAPI xll_prob_normal_pdf(double x)
{
#pragma XLLEXPORT
	doublex y;

	try {
		y = normal<>::pdf(x);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return y;
}