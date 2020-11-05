#pragma once
#if !defined(_TRIG_FUNCTIONS)
#define _TRIG_FUNCTIONS

#include"sse_macros.h"


extern "C" bool pcos_sse_(double const* x, int n, double* result);



namespace packed_sse {

	bool pcos_sse(double const* x, int evenSize, double* result) {
		return pcos_sse_(x, evenSize, result);
	}







}






#endif ///_TRIG_FUNCTIONS