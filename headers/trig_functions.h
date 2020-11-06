#pragma once
#if !defined(_TRIG_FUNCTIONS)
#define _TRIG_FUNCTIONS

#include"sse_macros.h"


extern "C" bool cos_sse_pd(double const* x, int n, double* out);
extern "C" bool cos_sse_ps(float const* x, int n, float* out);


namespace packed_sse {

	bool cos_sse_packed(double const* x, int size2, double* result) {
		return cos_sse_pd(x, size2, result);
	}

	bool cos_sse_packed(float const* x, int size4, float* result) {
		return cos_sse_ps(x, size4, result);
	}







}






#endif ///_TRIG_FUNCTIONS