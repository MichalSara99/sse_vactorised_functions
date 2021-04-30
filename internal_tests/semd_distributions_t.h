#if !defined(_SEMD_DISTRIBUTIONS_T_H_)
#define _SEMD_DISTRIBUTIONS_T_H_

#include "semd/semd_distributions.h"
#include <chrono>
#include <iostream>
#include <random>

template <typename fp_type> fp_type norm_cdf(fp_type x)
{
    const fp_type pi = sse_constants::pi<fp_type>();
    fp_type ind = 0.0f;
    if (x <= static_cast<fp_type>(0.0))
        ind = static_cast<fp_type>(1.0);
    x = std::abs(x);
    fp_type const cst = static_cast<fp_type>(1.0) / (std::sqrt(static_cast<fp_type>(2.0) * pi));
    fp_type const first = std::exp(-static_cast<fp_type>(0.5) * x * x);
    fp_type const second = static_cast<fp_type>(0.226) + static_cast<fp_type>(0.64) * x +
                           static_cast<fp_type>(0.33) * std::sqrt(x * x + static_cast<fp_type>(3.0));
    fp_type const res = static_cast<fp_type>(1.0) - ((first / second) * cst);
    return std::abs(ind - res);
}
template <typename fp_type> fp_type norm_pdf(fp_type x)
{
    const fp_type pi = sse_constants::pi<fp_type>();
    fp_type const cst = static_cast<fp_type>(1.0) / (std::sqrt(static_cast<fp_type>(2.0) * pi));
    fp_type const first = std::exp(-static_cast<fp_type>(0.5) * x * x);
    return cst * first;
}

template <typename fp_type> fp_type rationalApproxIncCDF(fp_type x)
{
    fp_type const c[3] = {static_cast<fp_type>(2.515517), static_cast<fp_type>(0.802853),
                          static_cast<fp_type>(0.010328)};
    fp_type const d[3] = {static_cast<fp_type>(1.432788), static_cast<fp_type>(0.189269),
                          static_cast<fp_type>(0.001308)};
    return (x - ((c[2] * x + c[1]) * x + c[0]) / (((d[2] * x + d[1]) * x + d[0]) * x + 1.0f));
}

template <typename fp_type> fp_type inv_cdf(fp_type p)
{
    int ind = 0;
    int inv = -1;
    if (p >= static_cast<fp_type>(0.5))
    {
        ind = 1;
        inv = 1;
    }
    p = abs(ind - p);
    fp_type const x = std::sqrt(static_cast<fp_type>(-2.0) * std::log(p));
    return (inv * rationalApproxIncCDF<fp_type>(x));
}

template <typename T> void testSemdNormCDF()
{

    std::uniform_real_distribution<double> unif(-5.0, 5.05);
    std::default_random_engine re;
    const int n = 100;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_distributions::normal::cdf(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = norm_cdf<T>(v1[t]);
    }
    auto end_cpp = std::chrono::system_clock::now();
    auto elapsed_cpp = std::chrono::duration<T>(end_cpp - start_cpp).count();

#ifdef _SEE_VALUES_
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
#endif
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdNormPDF()
{
    std::uniform_real_distribution<double> unif(-5.0, 5.05);
    std::default_random_engine re;
    const int n = 100;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_distributions::normal::pdf(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = norm_pdf<T>(v1[t]);
    }
    auto end_cpp = std::chrono::system_clock::now();
    auto elapsed_cpp = std::chrono::duration<T>(end_cpp - start_cpp).count();

#ifdef _SEE_VALUES_
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
#endif
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdNormInvCDF()
{
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::default_random_engine re;
    const int n = 100;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_distributions::normal::invcdf(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = inv_cdf<T>(static_cast<T>(v1[t]));
    }
    auto end_cpp = std::chrono::system_clock::now();
    auto elapsed_cpp = std::chrono::duration<T>(end_cpp - start_cpp).count();
#ifdef _SEE_VALUES_
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
#endif
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

#endif ///_SEMD_DISTRIBUTIONS_T_H_
