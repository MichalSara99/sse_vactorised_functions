#include <iostream>
#include <string>

// EXTERNAL TESTS
#include "external_tests/basic_functions_et.h"
#include "external_tests/basic_operations_et.h"
#include "external_tests/exp_functions_et.h"
#include "external_tests/log_functions_et.h"
#include "external_tests/normal_dist_functions_et.h"
#include "external_tests/special_functions_et.h"
#include "external_tests/trig_functions_et.h"

// INTERNAl TESTS:
#include "internal_tests/semd_functions_t.h"
#include "internal_tests/semd_operations_t.h"
#include "internal_tests/semd_t.h"

int main(int argc, char const *argv[])
{

    /// ==========================================================
    /// =================== INTERNAL TESTS =======================
    /// ==========================================================

    // ===================================================
    // ====================== semd_t.h ===================

    // testSemdFromList();
    // testSemdFromVector();
    // testSemdFromConstVal();
    // testSemdFromSize();
    // testSemdFromCopy();
    // testSemdFromMove();
    // testSemdCopyAssign();
    // testSemdMoveAssign();

    // ===================================================
    // ================== semd_operations.h ==============
    // testSemdOperationsAdd<double>();
    // testSemdOperationsSub<double>();

    // ===================================================
    // ================== semd_functions.h ==============
    // testSemdSin<double>();
    // testSemdCos<double>();
    // testSemdExpFast<double>();
    // testSemdExp<double>();
    // testSemdLog<double>();

    /// ==========================================================
    /// =================== EXTERNAL TESTS =======================
    /// ==========================================================

    // ===================================================
    // ================ trig_functions_et.h ===============

    // testBasicSinSSEDouble();
    // testBasicSinSSEFloat();
    // testBasicCosSSEDouble();
    // testBasicCosSSEFloat();
    // testBasicTanSSEFloat();
    // testBasicCotSSEFloat();

    // ==================================================

    // ==================================================
    // ================ exp_functions_et.h ===============

    // testBasicFastExpSSEDouble();
    // testBasicFastExpSSEFloat();
    // testBasicExpSSEDouble();
    // testBasicExpSSEFloat();

    // ==================================================

    // ==================================================
    // ================ log_functions_et.h ===============

    // testBasicLogSSEFloat();
    // testBasicLogSSEDouble();

    // ==================================================

    // ==================================================
    // ================ basic_functions_et.h =============

    // testBasicAbsSSEFloat();
    // testBasicAbsSSEDouble();
    // testBasicSqrtSSEDouble();
    // testBasicSqrtSSEFloat();
    // testBasicMinsSSEFloat();
    // testBasicMinsSSEDouble();
    // testBasicMaxsSSEFloat();
    // testBasicMaxsSSEDouble();
    // testBasicSqrpowSSEDouble();
    // testBasicSqrpowSSEFloat();

    // ==================================================

    // ==================================================
    // ================ basic_operations_et.h ============

    // testBasicInvSSEFloat();
    // testBasicInvSSEDouble();
    // testBasicNegSSEFloat();
    // testBasicNegSSEDouble();
    // testBasicSubSSEDouble();
    // testBasicSubSSEFloat();
    // testBasicAddSSEDouble();
    // testBasicAddSSEFloat();
    // testBasicMulSSEFloat();
    // testBasicMulSSEDouble();
    // testBasicDivSSEDouble();
    // testBasicDivSSEFloat();

    // ==================================================
    // ==================================================

    // ================ special_functions_et.h ===========

    // testErfSSEDouble();
    // testErfSSEFloat();
    // testErfcSSEDouble();
    // testErfcSSEFloat();

    // ==================================================

    // ==================================================
    // ================ normal_dist_functions_et.h =======

    // testBasicNormPDFSSEFloat();
    // testBasicNormPDFSSEDouble();
    // testBasicNormCDFSSEFloat();
    // testBasicNormCDFSSEDouble();
    // testBasicNormInvCDFSSEFloat();
    // testBasicNormInvCDFSSEDouble();

    // ==================================================

    std::cin.get();
    std::cin.get();
    return 0;
}
