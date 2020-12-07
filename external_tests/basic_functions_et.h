#pragma once
#if !defined(_BASIC_FUNCTIONS_ET)
#define _BASIC_FUNCTIONS_ET

#include<iostream>
#include<iomanip>
#include<chrono>
#include<random>
#include<sse_math_x86_lib.h>

#include"external_headers/sse_macros.h"


using namespace sse_basics;


void testBasicMaxsSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* y = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	y[0] = 0.0;
	y[1] = pi() / 2.0;
	y[2] = pi();
	y[3] = 3.0 * pi() / 2.0;
	y[4] = 5.0 * pi() / 4.0;
	y[5] = 2.0 * pi();
	y[6] = pi();
	y[7] = 3.0 * pi();
	y[8] = 6.0 * pi() / 3.0;
	y[9] = 2.0 * pi();
	y[10] = pi() / 4.0;
	y[11] = 7.0 * pi() / 4.0;
	y[12] = 0.5;
	y[13] = 1.0 / 3.0;
	y[14] = -23.5;
	y[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = maxs_sse(x, y, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = std::max(x[i], y[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed maxs SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "max(" << x[i] << "," << y[i] << ") = " << res2[i] << " | " << res1[i] << " | " << (res1[i] - res2[i]) << "\n";
	}
	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(y);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}

void testBasicMaxsSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double* y = sse_utility::aligned_alloc<double>(n, align);
	double* res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	y[0] = 0.0;
	y[1] = pi() / 2.0;
	y[2] = pi();
	y[3] = 3.0 * pi() / 2.0;
	y[4] = 5.0 * pi() / 4.0;
	y[5] = 2.0 * pi();
	y[6] = pi();
	y[7] = 3.0 * pi();
	y[8] = 6.0 * pi() / 3.0;
	y[9] = 2.0 * pi();
	y[10] = pi() / 4.0;
	y[11] = 7.0 * pi() / 4.0;
	y[12] = 0.5;
	y[13] = 1.0 / 3.0;
	y[14] = -23.5;
	y[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = maxs_sse(x, y, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = std::max(x[i], y[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed maxs SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "max(" << x[i] << "," << y[i] << ") = " << res2[i] << " | " << res1[i] << " | " << (res1[i] - res2[i]) << "\n";
	}

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(y);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}



void testBasicMinsSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* y = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	y[0] = 0.0;
	y[1] = pi() / 2.0;
	y[2] = pi();
	y[3] = 3.0 * pi() / 2.0;
	y[4] = 5.0 * pi() / 4.0;
	y[5] = 2.0 * pi();
	y[6] = pi();
	y[7] = 3.0 * pi();
	y[8] = 6.0 * pi() / 3.0;
	y[9] = 2.0 * pi();
	y[10] = pi() / 4.0;
	y[11] = 7.0 * pi() / 4.0;
	y[12] = 0.5;
	y[13] = 1.0 / 3.0;
	y[14] = -23.5;
	y[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = mins_sse(x, y , n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = std::min(x[i], y[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed mins SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	for (int i = 0; i < n; ++i) {
		std::cout << "min(" << x[i] << "," << y[i] << ") = " << res2[i] << " | " << res1[i] << " | " << (res1[i] - res2[i]) << "\n";
	}
	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(y);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}

void testBasicMinsSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double* y = sse_utility::aligned_alloc<double>(n, align);
	double* res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	y[0] = 0.0;
	y[1] = pi() / 2.0;
	y[2] = pi();
	y[3] = 3.0 * pi() / 2.0;
	y[4] = 5.0 * pi() / 4.0;
	y[5] = 2.0 * pi();
	y[6] = pi();
	y[7] = 3.0 * pi();
	y[8] = 6.0 * pi() / 3.0;
	y[9] = 2.0 * pi();
	y[10] = pi() / 4.0;
	y[11] = 7.0 * pi() / 4.0;
	y[12] = 0.5;
	y[13] = 1.0 / 3.0;
	y[14] = -23.5;
	y[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = mins_sse(x,y, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = std::min(x[i],y[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed mins SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	for (int i = 0; i < n; ++i) {
		std::cout <<"min("<<x[i]<<","<<y[i]<<") = "<< res2[i] << " | " << res1[i] << " | " << (res1[i] - res2[i]) << "\n";
	}

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(y);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}


void testBasicMinSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float res1;
	float res2;

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = min_sse(x, n, &res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	res2 = x[0];
	for (int i = 0; i < n; ++i) {
		if (x[i] < res2)
			res2 = x[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed min SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	std::cout << res2 << " | " << res1 << " | " << (res1 - res2) << "\n";

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
}

void testBasicMinSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double res1;
	double res2;

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = -100*pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = min_sse(x, n, &res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	res2 = x[0];
	for (int i = 0; i < n; ++i) {
		if (x[i] < res2)
			res2 = x[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed min SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	std::cout << res2 << " | " << res1 << " | " << (res1 - res2) << "\n";

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
}


void testBasicMaxSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float res1;
	float res2;

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = max_sse(x, n, &res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	res2 = x[0];
	for (int i = 0; i < n; ++i) {
		if (x[i] > res2)
			res2 = x[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed max SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	std::cout << res2 << " | " << res1 << " | " << (res1 - res2) << "\n";

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
}

void testBasicMaxSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double res1;
	double res2;

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = -100 * pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = -23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = max_sse(x, n, &res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	res2 = x[0];
	for (int i = 0; i < n; ++i) {
		if (x[i] > res2)
			res2 = x[i];
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed max SSE occured");

	std::cout << "		C++				Assembly (SSE)			Difference\n";
	std::cout << "=========================================================\n\n";
	std::cout << res2 << " | " << res1 << " | " << (res1 - res2) << "\n";

	std::cout << "=========================================================\n\n";
	std::cout << "\n" << "Elapsed (C++): " << elapsed_cpp;
	std::cout << "\n" << "Elapsed (Assembly): " << elapsed_asm << "\n";

	sse_utility::aligned_free(x);
}


void testBasicSqrtSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double* res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = sqrt_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = sqrt(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed sqrt SSE occured");

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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}

void testBasicSqrtSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = sqrt_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = sqrt(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed sqrt SSE occured");

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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}

void testBasicAbsSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double *res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = -2.0 * pi();
	x[10] = -pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = abs_sse(x, n, res1);
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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}


void testBasicAbsSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double* res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0f;
	x[1] = pi() / 2.0f;
	x[2] = pi();
	x[3] = 3.0f * pi() / 2.0f;
	x[4] = 5.0f * pi() / 4.0f;
	x[5] = 2.0f * pi();
	x[6] = 4.0f * pi();
	x[7] = 3.0f * pi();
	x[8] = 6.0f * pi() / 3.0f;
	x[9] = -2.0f * pi();
	x[10] = -pi() / 4.0f;
	x[11] = 7.0f * pi() / 4.0f;
	x[12] = 0.5f;
	x[13] = pi() / 3.0f;
	x[14] = 23.5f;
	x[15] = 4.0f * pi() / 3.0f;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = abs_sse(x, n, res1);
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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}


void testBasicSqrpowSSEDouble() {

	int const n = 16;
	std::size_t const align = 16;

	double* x = sse_utility::aligned_alloc<double>(n, align);
	double* res1 = sse_utility::aligned_alloc<double>(n, align);
	double* res2 = sse_utility::aligned_alloc<double>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = sqrpow_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = pow(x[i],2);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed sqrpow SSE occured");

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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}

void testBasicSqrpowSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

	// test some basic known values:

	x[0] = 0.0;
	x[1] = pi() / 2.0;
	x[2] = pi();
	x[3] = 3.0 * pi() / 2.0;
	x[4] = 5.0 * pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = 2.0 * pi();
	x[10] = pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 23.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = sqrpow_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = pow(x[i], 2);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed sqrpow SSE occured");

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

	sse_utility::aligned_free(x);
	sse_utility::aligned_free(res1);
	sse_utility::aligned_free(res2);
}





#endif ///_BASIC_FUNCTIONS_ET