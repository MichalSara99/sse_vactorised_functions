#pragma once
#if !defined(_SEMD_DISTRIBUTIONS_H_)
#define _SEMD_DISTRIBUTIONS_H_

#include "macros/sse_macros.h"
#include "semd.h"
#include <sse_math_x86_lib.h>

namespace semd_distributions
{

namespace normal
{
template <typename fp_type> semd<fp_type> const cdf(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_normal_distribution::norm_cdf_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const pdf(semd<fp_type> const &arg)
{
    semd<fp_type> res(arg.size());
    SSE_ASSERT(sse_normal_distribution::norm_pdf_sse<fp_type>(arg.data(), arg.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

template <typename fp_type> semd<fp_type> const invcdf(semd<fp_type> const &prob)
{
    semd<fp_type> res(prob.size());
    SSE_ASSERT(sse_normal_distribution::norm_inv_cdf_sse<fp_type>(prob.data(), prob.size(), res.data()) == 1,
               "operation must return 1 to be successfull");
    return res;
}

} // namespace normal

} // namespace semd_distributions

#endif ///_SEMD_OPERATIONS_H_
