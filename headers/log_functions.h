#pragma once
#if !defined(_LOG_FUNCTIONS)
#define _LOG_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {

	// packed single-precision floating-point natural log
	extern "C" bool log_sse_ps(float const* in_aligned_16, int n, float* out_aligned_16);
	// packed double-precision floating-point natural log
	extern "C" bool log_sse_pd(double const* in_aligned_16, int n, double* out_aligned_16);

}

namespace sse_math {

	// packed fast single-precision floating-point natural log
	bool log_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::log_sse_ps(in_aligned_16, size4, out_aligned_16);
	}

	// packed fast double-precision floating-point natural log
	bool log_sse_packed(double const* in_aligned_16, int size4, double* out_aligned_16) {
		return __packed_sse_::log_sse_pd(in_aligned_16, size4, out_aligned_16);
	}



}

#endif ///_LOG_FUNCTIONS