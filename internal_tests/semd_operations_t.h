#if !defined(_SEMD_OPERATIONS_T_H_)
#define _SEMD_OPERATIONS_T_H_

#include "semd/semd_operations.h"
#include <chrono>
#include <iostream>
#include <random>

using namespace semd_operations;

template <typename T> void testSemdOperationsAdd()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    std::vector<T> v2(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
        v2[t] = unif(re);
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    semd<T> s2(v2);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = s1 + s2;
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = v1[t] + v2[t];
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

template <typename T> void testSemdOperationsSub()
{
    std::uniform_real_distribution<T> unif(-50.0, 38.05);
    std::default_random_engine re;
    const int n = 1025;
    std::vector<T> v1(n);
    std::vector<T> v2(n);
    for (std::size_t t = 0; t < n; ++t)
    {
        v1[t] = unif(re);
        v2[t] = unif(re);
    }

    std::vector<T> r(v1.size());

    semd<T> s1(v1);
    semd<T> s2(v2);
    auto start_semd = std::chrono::system_clock::now();
    auto const res = s1 - s2;
    auto end_semd = std::chrono::system_clock::now();
    auto elapsed_semd = std::chrono::duration<T>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::system_clock::now();
    for (std::size_t t = 0; t < r.size(); ++t)
    {
        r[t] = v1[t] - v2[t];
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

#endif ///_SEMD_OPERATIONS_T_H_
