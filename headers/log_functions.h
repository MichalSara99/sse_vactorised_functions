#pragma once
#if !defined(_LOG_FUNCTIONS)
#define _LOG_FUNCTIONS

#include"sse_macros.h"

namespace __packed_sse_ {

	// packed single-precision floating-point cosine
	extern "C" bool log_sse_ps(float const* in_aligned_16, int n, float* out_aligned_16);

}

namespace packed_sse {

	// packed fast single-precision floating-point cosine
	bool log_sse_packed(float const* in_aligned_16, int size4, float* out_aligned_16) {
		return __packed_sse_::log_sse_ps(in_aligned_16, size4, out_aligned_16);
	}



}

#endif ///_LOG_FUNCTIONS