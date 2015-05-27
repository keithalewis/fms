// timer.h - timing functions
#pragma once
#include <chrono>

namespace timer {

	template<class F>
	inline std::chrono::milliseconds time(const F& f, size_t n = 1)
	{
		using namespace std::chrono;

		auto b = high_resolution_clock::now();
		while (n--)
			f();
		auto e = high_resolution_clock::now();

		return duration_cast<milliseconds>(e - b);
	}

} // timer
#ifdef _DEBUG
#include <functional>
#include <thread>
#include "ensure.h"

#ifdef _WIN32
//extern "C" void __stdcall Sleep(unsigned long);
//#define sleep Sleep
#endif

inline void test_timer()
{
	using namespace std::chrono;

	auto 
	d = timer::time([]() { Sleep(10); });
	ensure (d.count() >= 10);
	ensure (d.count() - 10 < 10);

	d = timer::time([]() { Sleep(100); });
	ensure (d.count() >= 100);
	ensure (d.count() - 100 < 10);

	d = timer::time([]() { Sleep(10); }, 10);
	ensure (d.count() >= 100);
	ensure (d.count() - 100 < 60);
}

#endif // _DEBUG