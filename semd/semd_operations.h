#pragma once
#if !defined(_SEMD_OPERATIONS_H_)
#define _SEMD_OPERATIONS_H_

#include "semd.h"
#include <sse_math_x86_lib.h>

namespace semd_operations
{
template <typename fp_type> semd<fp_type> const operator+(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    // TODO: assert same sizes:
    semd<fp_type> res(op1.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::add_sse(op1.data(), op2.data(), op1.size(), res.data());
    return res;
}

template <typename fp_type> semd<fp_type> const operator-(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    // TODO: assert same sizes:
    semd<fp_type> res(op1.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::sub_sse(op1.data(), op2.data(), op1.size(), res.data());
    return res;
}

} // namespace semd_operations

#endif ///_SEMD_OPERATIONS_H_
