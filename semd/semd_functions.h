#pragma once
#if !defined(_SEMD_FUNCTIONS_H_)
#define _SEMD_FUNCTIONS_H_

#include "macros/sse_macros.h"
#include "semd.h"
#include <sse_math_x86_lib.h>

namespace semd_functions
{
template <typename fp_type> semd<fp_type> const sin(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::sin_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const cos(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::cos_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const exp_fast(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::exp_fast_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const exp(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::exp_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const log(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::log_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const abs(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::abs_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const sqrt(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::sqrt_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const mins(semd<fp_type> const &arg1, semd<fp_type> const &arg2)
{
    SSE_ASSERT(arg1.size() == arg2.size(), "sizes of semd must be same");
    semd<fp_type> res(arg1.size());
    SSE_ASSERT(sse_basics::mins_sse<fp_type>(arg1.data(), arg2.data(), arg1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const maxs(semd<fp_type> const &arg1, semd<fp_type> const &arg2)
{
    SSE_ASSERT(arg1.size() == arg2.size(), "sizes of semd must be same");
    semd<fp_type> res(arg1.size());
    SSE_ASSERT(sse_basics::maxs_sse<fp_type>(arg1.data(), arg2.data(), arg1.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const sqrpow(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_basics::sqrpow_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const erf(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_specials::erf_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const erfc(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_specials::erfc_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

} // namespace semd_functions

#endif ///_SEMD_FUNCTIONS_H_
