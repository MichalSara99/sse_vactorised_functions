#pragma once
#if !defined(_NORMAL_DIST_FUNCTIONS)
#define _NORMAL_DIST_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {

	// packed single-precision floating-point normal CDF
	extern "C" bool norm_cdf_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);

	// packed double-precision floating-point normal CDF
	extern "C" bool norm_cdf_sse_pd(double const* in_aligned_16, int n4, double* out_aligned_16);

	// packed single-precision floating-point inverse normal CDF
	extern "C" bool norm_inv_cdf_sse_ps(float const* in_aligned_16, int n4, float* out_aligned_16);

}	






namespace sse_math {

	// packed single-precision floating-point normal CDF
	bool norm_cdf_sse_packed(float const* in_aligned_16, int size2, float* out_aligned_16) {
		return __packed_sse_::norm_cdf_sse_ps(in_aligned_16, size2, out_aligned_16);
	}

	// packed double-precision floating-point normal CDF
	bool norm_cdf_sse_packed(double const* in_aligned_16, int size2, double* out_aligned_16) {
		return __packed_sse_::norm_cdf_sse_pd(in_aligned_16, size2, out_aligned_16);
	}

	// packed single-precision floating-point inverse normal CDF
	bool norm_inv_cdf_sse_packed(float const* in_aligned_16, int size2, float* out_aligned_16) {
		return __packed_sse_::norm_inv_cdf_sse_ps(in_aligned_16, size2, out_aligned_16);
	}

}






#endif ///_NORMAL_DIST_FUNCTIONS