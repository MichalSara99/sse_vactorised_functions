#if !defined(_SEMD_FUNCTIONS_T_H_)
#define _SEMD_FUNCTIONS_T_H_

#include "semd/semd_functions.h"
#include <chrono>
#include <iostream>
#include <random>

template <typename T> void testSemdSin()
{

    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::sin(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::sin(v1[t]);
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

template <typename T> void testSemdCos()
{
    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::cos(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::cos(v1[t]);
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

template <typename T> void testSemdExpFast()
{
    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::exp_fast(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::exp(v1[t]);
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

template <typename T> void testSemdExp()
{
    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::exp(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::exp(v1[t]);
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

template <typename T> void testSemdLog()
{
    std::uniform_real_distribution<double> unif(-1.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::log(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::log(v1[t]);
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

template <typename T> void testSemdAbs()
{
    std::uniform_real_distribution<double> unif(-51.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::abs(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::abs(v1[t]);
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

template <typename T> void testSemdSqrt()
{
    std::uniform_real_distribution<double> unif(-51.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::sqrt(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::sqrt(v1[t]);
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

template <typename T> void testSemdSqrPow()
{
    std::uniform_real_distribution<double> unif(-51.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::sqrpow(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = v1[t] * v1[t];
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

template <typename T> void testSemdMins()
{
    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    std::vector<T> v2(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
        v2[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());
    //#define _SEE_VALUES_
    semd<T> s1(v1);
    semd<T> s2(v2);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::mins(s1, s2);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = (v1[t] < v2[t]) ? v1[t] : v2[t];
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

template <typename T> void testSemdMaxs()
{
    std::uniform_real_distribution<double> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 100000;
    std::vector<T> v1(n);
    std::vector<T> v2(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
        v2[t] = static_cast<T>(unif(re));
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    semd<T> s2(v2);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::maxs(s1, s2);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = (v1[t] > v2[t]) ? v1[t] : v2[t];
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

template <typename T> void testSemdErf()
{
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::default_random_engine re;
    const int n = 100;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = static_cast<T>(unif(re));
    }
#define _SEE_VALUES_
    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = semd_functions::erf(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::erf(v1[t]);
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

template <typename T> void testSemdErfc()
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
    auto const res = semd_functions::erfc(s1);
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = std::erfc(v1[t]);
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

#endif ///_SEMD_FUNCTIONS_T_H_
