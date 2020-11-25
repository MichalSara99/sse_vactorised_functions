#pragma once
#if !defined(_SPECIAL_FUNCTIONS)
#define _SPECIAL_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {
	// packed double-precision floating-point error function
	extern "C" bool erf_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point error function
	extern "C" bool erf_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);

	// packed double-precision floating-point complementary error function
	extern "C" bool erfc_sse_pd(double const* in_aligned_16, int n2, double* out_aligned_16);
	// packed single-precision floating-point complementary error function
	extern "C" bool erfc_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);
}


namespace sse_math {

	// packed double-precision floating-point error function
	bool erf_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::erf_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point error function
	bool erf_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::erf_sse_ps(in_aligned_16, size4, out_aligned_16);
	}
	// packed double-precision floating-point complementary error function
	bool erfc_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::erfc_sse_pd(in_aligned_16, size2, out_aligned_16);
	}
	// packed single-precision floating-point complementary error function
	bool erfc_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::erfc_sse_ps(in_aligned_16, size4, out_aligned_16);
	}






}






#endif ///_SPECIAL_FUNCTIONS