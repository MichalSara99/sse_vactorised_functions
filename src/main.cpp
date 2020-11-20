#include<iostream>
#include<string>


#include"unit_tests/trig_functions_t.h"
#include"unit_tests/exp_functions_t.h"
#include"unit_tests/log_functions_t.h"
#include"unit_tests/basic_functions_t.h"
#include"unit_tests/normal_dist_functions_t.h"

int main(int argc, char const* argv[]) {

	// ===================================================
	// ================ trig_functions_t.h ===============

	// testBasicSinSSEDouble();
	// testBasicSinSSEFloat();
	// testBasicCosSSEDouble();
	// testBasicCosSSEFloat();

	// ==================================================


	// ==================================================
	// ================ exp_functions_t.h ===============
	
	// testBasicFastExpSSEDouble();
	// testBasicFastExpSSEFloat();
	// testBasicExpSSEDouble();
	// testBasicExpSSEFloat();

	// ==================================================

	// ==================================================
	// ================ log_functions_t.h ===============

	// testBasicLogSSEFloat();
	// testBasicLogSSEDouble();

	// ==================================================

	// ==================================================
	// ================ basic_functions_t.h ===============

	// testBasicAbsSSEDouble();
	// testBasicAbsSSEFloat();
	// testBasicMulSSEFloat();
	// testBasicMulSSEDouble();

		// ==================================================

	// ==================================================
	// ================ normal_dist_functions_t.h ===============

	testBasicNormCDFSSEFloat();

	// ==================================================



	std::cin.get();
	std::cin.get();
	return 0;
}
												