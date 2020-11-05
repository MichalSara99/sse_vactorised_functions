#pragma once
#if !defined(_TRIG_FUNCTIONS_T)
#define _TRIG_FUNCTIONS_T

#include<iostream>
#include<iomanip>
#include<chrono>
#include<new>
#include<random>

#include"headers/math_constants.h"
#include"headers/trig_functions.h"
#include"headers/sse_macros.h"

using math_constants::pi;
using packed_sse::pcos_sse;


void testBasicPCosSSE() {

	int const n = 16;

	double* x = (double*)operator new[](sizeof(double)* n, std::align_val_t(16));
	double* res1 = (double*)operator new[](sizeof(double)* n, std::align_val_t(16));
	double* res2 = (double*)operator new[](sizeof(double)* n, std::align_val_t(16));

	// test some basic known values:

	x[0] = 0.0;					
	x[1] = pi / 2;				
	x[2] = pi;					
	x[3] = 3.0 * pi / 2.0;		
	x[4] = 5.0 * pi / 4.0;		
	x[5] = 2.0 * pi;				
	x[6] = 4.0 * pi;			
	x[7] = 3.0 * pi;				  	 
	x[8] = 6.0 * pi / 3.0;       
	x[9] = -2.0 * pi;			
	x[10] = -pi / 4.0;			
	x[11] = 7.0 * pi / 4.0;		
	x[12] = 0.5;
	x[13] = pi / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = pcos_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = cos(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed cosine SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	for (int i = 0; i < n; ++i) {
		std::cout << i << " | " << res2[i];
		std::cout << " | " << res1[i];
		std::cout << " | " << (res1[i] - res2[i]) << "\n";
	}
	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

}











#endif ///_TRIG_FUNCTIONS_T