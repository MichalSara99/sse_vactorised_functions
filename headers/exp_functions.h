#pragma once
#if !defined(_EXP_FUNCTIONS)
#define _EXP_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {
	// packed fast single-precision floating-point cosine
	extern "C" bool exp_fast_sse_ps(float const* in_aligned_16, int n, float* out_aligned_16);

	// packed fast double-precision floating-point sine
	extern "C" bool exp_fast_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);

}

namespace packed_sse {

	// packed fast double-precision floating-point cosine
	bool exp_fast_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::exp_fast_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed fast single-precision floating-point cosine
	bool exp_fast_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::exp_fast_sse_ps(in_aligned_16, size4, out_aligned_16);
	}



}

#endif ///_EXP_FUNCTIONS