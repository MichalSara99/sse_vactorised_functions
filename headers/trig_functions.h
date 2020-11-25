#pragma once
#if !defined(_TRIG_FUNCTIONS)
#define _TRIG_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {
	// packed double-precision floating-point cosine
	extern "C" bool cos_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point cosine
	extern "C" bool cos_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);

	// packed double-precision floating-point sine
	extern "C" bool sin_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point sine
	extern "C" bool sin_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);
}


namespace sse_math {

	// packed double-precision floating-point cosine
	bool cos_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::cos_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point cosine
	bool cos_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::cos_sse_ps(in_aligned_16, size4, out_aligned_16);
	}
	// packed double-precision floating-point sine
	bool sin_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::sin_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point sine
	bool sin_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::sin_sse_ps(in_aligned_16, size4, out_aligned_16);
	}






}






#endif ///_TRIG_FUNCTIONS