#pragma once
#if !defined(_SEMD_FUNCTIONS_H_)
#define _SEMD_FUNCTIONS_H_

#include "semd.h"
#include <sse_math_x86_lib.h>

namespace semd_functions
{
template <typename fp_type> semd<fp_type> const sin(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::sin_sse(arg.data(), arg.size(), res.data());
    return res;
}

template <typename fp_type> semd<fp_type> const cos(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::cos_sse(arg.data(), arg.size(), res.data());
    return res;
}

template <typename fp_type> semd<fp_type> const exp_fast(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::exp_fast_sse(arg.data(), arg.size(), res.data());
    return res;
}

template <typename fp_type> semd<fp_type> const exp(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::exp_sse(arg.data(), arg.size(), res.data());
    return res;
}

template <typename fp_type> semd<fp_type> const log(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    // TODO: assert return from add_sse to make sure it was success:
    sse_basics::log_sse(arg.data(), arg.size(), res.data());
    return res;
}

} // namespace semd_functions

#endif ///_SEMD_FUNCTIONS_H_
