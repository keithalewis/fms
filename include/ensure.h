// ensure.h - assert replacement that throws instead of calling abort()
// #define NENSURE
// before including to turn ensure checking off
#pragma once
#include <stdexcept>

#ifdef NENSURE
#define ensure(x)
#endif

#ifndef ensure

#define ENSURE_HASH_(x) #x
#define ENSURE_STRZ_(x) ENSURE_HASH_(x)
#define ENSURE_FILE "file: " __FILE__
#ifdef __FUNCTION__
#define ENSURE_FUNC "\nfunction: " __FUNCTION__
#else
#define ENSURE_FUNC ""
#endif
#define ENSURE_LINE "\nline: " ENSURE_STRZ_(__LINE__)
#define ENSURE_SPOT ENSURE_FILE ENSURE_LINE ENSURE_FUNC

#ifdef _DEBUG
	#ifdef _WIN32 // defined for 64 bit also
		extern "C" __declspec(dllimport) void __stdcall DebugBreak(void);
		#define ensure(e) if (!(e)) { DebugBreak(); \
		throw std::runtime_error(ENSURE_SPOT "\nensure: \"" #e "\" failed"); } \
		else (void)0;
	#else
		#define ensure(e) if (!(e)) { __builtin_trap(); }
	#endif

	#define DEBUG_(e) e
#else // release
	#define ensure(e) if (!(e)) \
		throw std::runtime_error(ENSURE_SPOT "\nensure: \"" #e "\" failed"); \
		else (void)0;

	#define DEBUG_(e)
#endif

#endif // ensure
