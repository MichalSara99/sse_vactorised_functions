#pragma once
#if !defined(_SEMD_OPERATIONS_H_)
#define _SEMD_OPERATIONS_H_

#include "macros/sse_macros.h"
#include "semd.h"
#include <sse_math_x86_lib.h>

namespace semd_operations
{
template <typename fp_type> semd<fp_type> const operator+(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    SSE_ASSERT(op1.size() == op2.size(), "sizes of semd must be same");
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::add_sse<fp_type>(op1.data(), op2.data(), op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator+(semd<fp_type> const &op1, fp_type const op2)
{
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::add_br_sse<fp_type>(op1.data(), op2, op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator+(fp_type const op1, semd<fp_type> const &op2)
{
    semd<fp_type> res(op2.size());
    SSE_ASSERT(sse_basics::add_br_sse<fp_type>(op2.data(), op1, op2.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator-(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    SSE_ASSERT(op1.size() == op2.size(), "sizes of semd must be same");
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::sub_sse<fp_type>(op1.data(), op2.data(), op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator-(semd<fp_type> const &op1, fp_type const op2)
{
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::sub_br_sse<fp_type>(op1.data(), op2, op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator-(fp_type const op1, semd<fp_type> const &op2)
{
    semd<fp_type> res(op2.size());
    SSE_ASSERT(sse_basics::sub_br_s_sse<fp_type>(op1, op2.data(), op2.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator*(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    SSE_ASSERT(op1.size() == op2.size(), "sizes of semd must be same");
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::mul_sse<fp_type>(op1.data(), op2.data(), op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator*(semd<fp_type> const &op1, fp_type const op2)
{
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::mul_br_sse<fp_type>(op1.data(), op2, op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator*(fp_type const op1, semd<fp_type> const &op2)
{
    semd<fp_type> res(op2.size());
    SSE_ASSERT(sse_basics::mul_br_sse<fp_type>(op2.data(), op1, op2.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator/(semd<fp_type> const &op1, semd<fp_type> const &op2)
{
    SSE_ASSERT(op1.size() == op2.size(), "sizes of semd must be same");
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::div_sse<fp_type>(op1.data(), op2.data(), op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator/(semd<fp_type> const &op1, fp_type const op2)
{
    semd<fp_type> res(op1.size());
    SSE_ASSERT(sse_basics::div_br_sse<fp_type>(op1.data(), op2, op1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator/(fp_type const op1, semd<fp_type> const &op2)
{
    semd<fp_type> res(op2.size());
    SSE_ASSERT(sse_basics::div_br_s_sse<fp_type>(op1, op2.data(), op2.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const operator-(semd<fp_type> const &op)
{
    semd<fp_type> res(op.size());
    SSE_ASSERT(sse_basics::neg_sse<fp_type>(op.data(), op.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const inv(semd<fp_type> const &op)
{
    semd<fp_type> res(op.size());
    SSE_ASSERT(sse_basics::inv_sse<fp_type>(op.data(), op.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

} // namespace semd_operations

#endif ///_SEMD_OPERATIONS_H_
