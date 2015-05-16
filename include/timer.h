// timer.h - timing functions
#pragma once
#include <chrono>
#include <thread>

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
#include "ensure.h"

inline void test_timer()
{
	using namespace std::chrono;
	using std::this_thread::sleep_for;

	auto 
	d = timer::time([]() { sleep_for(milliseconds(10)); });
	ensure (d.count() >= 10);
	ensure (d.count() - 10 < 10);

	d = timer::time([]() { sleep_for(milliseconds(100)); });
	ensure (d.count() >= 100);
	ensure (d.count() - 100 < 10);

	d = timer::time([]() { sleep_for(milliseconds(10)); }, 10);
	ensure (d.count() >= 100);
	ensure (d.count() - 100 < 60);
}

#endif // _DEBUG