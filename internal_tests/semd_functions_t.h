#if !defined(_SEMD_FUNCTIONS_T_H_)
#define _SEMD_FUNCTIONS_T_H_

#include "semd/semd_functions.h"
#include <chrono>
#include <iostream>
#include <random>

template <typename T> void testSemdSin()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
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

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdCos()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
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

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdExpFast()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
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

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdExp()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
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

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

template <typename T> void testSemdLog()
{
    std::uniform_real_distribution<T> unif(-1.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
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

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << t << ": " << r[t] << "|" << res[t] << "| " << (r[t] - res[t]) << "\n";
    }
    std::cout << "\n";
    std::cout << "=========================================================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp;
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << "\n";
}

#endif ///_SEMD_FUNCTIONS_T_H_
