#pragma once
#if !defined(_BASIC_FUNCTIONS)
#define _BASIC_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {

	// packed double-precision floating-point absolute value
	extern "C" bool abs_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point absolute value
	extern "C" bool abs_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);
	// packed double-precision floating-point square root 
	extern "C" bool sqrt_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point square root 
	extern "C" bool sqrt_sse_ps(float const* in_aligned_16, int n2, float* out_aligned_16);
}


namespace sse_math {

	// packed double-precision floating-point absolute value
	bool abs_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::abs_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point absolute value
	bool abs_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::abs_sse_ps(in_aligned_16, size4, out_aligned_16);
	}

	// packed double-precision floating-point negative value
	bool sqrt_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::sqrt_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point negative value
	bool sqrt_sse_packed(float const* in_aligned_16, int size2, float* out_aligned_16) {
		return __packed_sse_::sqrt_sse_ps(in_aligned_16, size2, out_aligned_16);
	}



}






#endif ///_BASIC_FUNCTIONS