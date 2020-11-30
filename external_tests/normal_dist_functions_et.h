#pragma once
#if !defined(_NORMAL_DIST_FUNCTIONS_ET)
#define _NORMAL_DIST_FUNCTIONS_ET

#include<iostream>
#include<iomanip>
#include<chrono>
#include<random>
#include<sse_math_x86_lib.h>

#include"external_headers/sse_macros.h"

using namespace sse_normal_distribution;

float norm_cdf(float x) {
	float ind = 0.0f;
	if (x <= 0.0f)
		ind = 1.0f;
	x = std::abs(x);
	float const cst = 1.0f / (std::sqrt(2.0f * pi()));
	float const first = std::exp(-0.5f * x * x);
	float const second = 0.226f + 0.64f * x + 0.33f * std::sqrt(x * x + 3.0f);
	float const res = 1.0f - ((first / second) * cst);
	return std::abs(ind - res);
}

double norm_cdf(double x) {
	double ind = 0.0;
	if (x <= 0.0)
		ind = 1.0;
	x = std::abs(x);
	double const cst = 1.0 / (std::sqrt(2.0 * pi()));
	double const first = std::exp(-0.5 * x * x);
	double const second = 0.226 + 0.64 * x + 0.33 * std::sqrt(x * x + 3.0);
	double const res = 1.0 - ((first / second) * cst);
	return std::abs(ind - res);
}


void testBasicNormCDFSSEDouble() {

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
	x[4] = 5.0* pi() / 4.0;
	x[5] = 2.0 * pi();
	x[6] = 4.0 * pi();
	x[7] = 3.0 * pi();
	x[8] = 6.0 * pi() / 3.0;
	x[9] = -2.0 * pi();
	x[10] = -pi() / 4.0;
	x[11] = 7.0 * pi() / 4.0;
	x[12] = 0.5;
	x[13] = pi() / 3.0;
	x[14] = 3.5;
	x[15] = 4.0 * pi() / 3.0;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = norm_cdf_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = norm_cdf(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed norm CDF SSE occured");

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

void testBasicNormCDFSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

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
	x[14] = 3.5f;
	x[15] = 4.0f * pi() / 3.0f;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = norm_cdf_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = norm_cdf(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed norm CDF SSE occured");

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

float rationalApproxIncCDF(float x) {
	float const c[3] = { 2.515517f, 0.802853f, 0.010328f };
	float const	d[3] = { 1.432788f, 0.189269f, 0.001308f };
	return (x - ((c[2] * x + c[1]) * x + c[0]) / (((d[2] * x + d[1]) * x + d[0]) * x + 1.0f));
}

float inv_cdf(float p) {
	int ind = 0;
	int inv = -1;
	if (p >= 0.5f) {
		ind = 1;
		inv = 1;
	}
	p = abs(ind - p);
	float const x = std::sqrt(-2.0f * std::log(p));
	return (inv * rationalApproxIncCDF(x));
}


void testBasicNormInvCDFSSEFloat() {

	int const n = 16;
	std::size_t const align = 16;

	float* x = sse_utility::aligned_alloc<float>(n, align);
	float* res1 = sse_utility::aligned_alloc<float>(n, align);
	float* res2 = sse_utility::aligned_alloc<float>(n, align);

	// test some basic known values:

	x[0] = 0.0000001f;
	x[1] = 0.00001f;
	x[2] = 0.001f;
	x[3] = 0.05f;
	x[4] = 0.15f;
	x[5] = 0.25f;
	x[6] = 0.35f;
	x[7] = 0.45f;
	x[8] = 0.55f;
	x[9] = 0.65f;
	x[10] = 0.75f;
	x[11] = 0.85f;
	x[12] = 0.95f;
	x[13] = 0.999f;
	x[14] = 0.99999f;
	x[15] = 0.9999999f;

	auto start_asm = std::chrono::system_clock::now();
	bool rc1 = norm_inv_cdf_sse(x, n, res1);
	auto end_asm = std::chrono::system_clock::now();
	auto elapsed_asm = std::chrono::duration<double>(end_asm - start_asm).count();

	auto start_cpp = std::chrono::system_clock::now();
	for (int i = 0; i < n; ++i) {
		res2[i] = inv_cdf(x[i]);
	}
	auto end_cpp = std::chrono::system_clock::now();
	auto elapsed_cpp = std::chrono::duration<double>(end_cpp - start_cpp).count();

	SSE_ASSERT(rc1 == 1, "Failure in packed norm INV CDF SSE occured");

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








#endif ///_NORMAL_DIST_FUNCTIONS_ET