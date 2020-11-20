#pragma once
#if !defined(_BASIC_FUNCTIONS_T)
#define _BASIC_FUNCTIONS_T

#include<iostream>
#include<iomanip>
#include<chrono>
#include<random>

#include"headers/sse_utilities.h"
#include"headers/sse_math_x86.h"
#include"headers/sse_macros.h"

using math_constants::pi;
using packed_sse::abs_sse_packed;
using packed_sse::mul_sse_packed;
using sse_utilities::aligned_alloc;
using sse_utilities::aligned_free;


void testBasicAbsSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = aligned_alloc<double>(n, align);
	double *res1 = aligned_alloc<double>(n, align);
	double* res2 = aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi / 2.0;
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
	bool rc1 = abs_sse_packed(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = abs(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed absolute value SSE occured");

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

	aligned_free(x);
	aligned_free(res1);
	aligned_free(res2);
}


void testBasicAbsSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = aligned_alloc<double>(n, align);
	double* res1 = aligned_alloc<double>(n, align);
	double* res2 = aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0f;
	x[1] = pi / 2.0f;
	x[2] = pi;
	x[3] = 3.0f * pi / 2.0f;
	x[4] = 5.0f * pi / 4.0f;
	x[5] = 2.0f * pi;
	x[6] = 4.0f * pi;
	x[7] = 3.0f * pi;
	x[8] = 6.0f * pi / 3.0f;
	x[9] = -2.0f * pi;
	x[10] = -pi / 4.0f;
	x[11] = 7.0f * pi / 4.0f;
	x[12] = 0.5f;
	x[13] = pi / 3.0f;
	x[14] = 23.5f;
	x[15] = 4.0f * pi / 3.0f;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = abs_sse_packed(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = abs(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed absolute value SSE occured");

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

	aligned_free(x);
	aligned_free(res1);
	aligned_free(res2);
}



void testBasicMulSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = aligned_alloc<double>(n, align);
	double* y = aligned_alloc<double>(n, align);
	double* res1 = aligned_alloc<double>(n, align);
	double* res2 = aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;					
	x[1] = pi / 2.0;				
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

	y[0] = 0.0;
	y[1] = pi / 2.0;
	y[2] = pi;
	y[3] = 3.0 * pi / 2.0;
	y[4] = 5.0 * pi / 4.0;
	y[5] = 2.0 * pi;
	y[6] = 4.0 * pi;
	y[7] = 3.0 * pi;
	y[8] = 6.0 * pi / 3.0;
	y[9] = -2.0 * pi;
	y[10] = -pi / 4.0;
	y[11] = 7.0 * pi / 4.0;
	y[12] = 0.5;
	y[13] = pi / 3.0;
	y[14] = 23.5;
	y[15] = 4.0 * pi / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = mul_sse_packed(x,y, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = x[i] * y[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed multiplication SSE occured");

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

	aligned_free(x);
	aligned_free(res1);
	aligned_free(res2);
}


void testBasicMulSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = aligned_alloc<double>(n, align);
	double* y = aligned_alloc<double>(n, align);
	double* res1 = aligned_alloc<double>(n, align);
	double* res2 = aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0f;
	x[1] = pi / 2.0f;
	x[2] = pi;
	x[3] = 3.0f * pi / 2.0f;
	x[4] = 5.0f * pi / 4.0f;
	x[5] = 2.0f * pi;
	x[6] = 4.0f * pi;
	x[7] = 3.0f * pi;
	x[8] = 6.0f * pi / 3.0f;
	x[9] = -2.0f * pi;
	x[10] = -pi / 4.0f;
	x[11] = 7.0f * pi / 4.0f;
	x[12] = 0.5f;
	x[13] = pi / 3.0f;
	x[14] = 23.5f;
	x[15] = 4.0f * pi / 3.0f;

	y[0] = 0.0;
	y[1] = pi / 2.0;
	y[2] = pi;
	y[3] = 3.0 * pi / 2.0;
	y[4] = 5.0 * pi / 4.0;
	y[5] = 2.0 * pi;
	y[6] = 4.0 * pi;
	y[7] = 3.0 * pi;
	y[8] = 6.0 * pi / 3.0;
	y[9] = -2.0 * pi;
	y[10] = -pi / 4.0;
	y[11] = 7.0 * pi / 4.0;
	y[12] = 0.5;
	y[13] = pi / 3.0;
	y[14] = 23.5;
	y[15] = 4.0 * pi / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = mul_sse_packed(x,y, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = x[i] * y[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed multiplication SSE occured");

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

	aligned_free(x);
	aligned_free(res1);
	aligned_free(res2);
}










#endif ///_BASIC_FUNCTIONS_T