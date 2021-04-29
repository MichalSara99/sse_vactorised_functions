#if !defined(_SEMD_T_H_)
#define _SEMD_T_H_

#include "semd/semd.h"
#include <iostream>

void testSemdFromList()
{
    // create semd from initializer list:
    semd<double> s1 = {1, 2, 3, 4, 5, 6, 7};

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
}

void testSemdFromVector()
{
    // create semd from vector:
    std::vector<double> vec = {1, 2, 3, 4, 5, 6, 7};
    semd<double> s1(vec);

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
}

void testSemdFromConstVal()
{
    // create semd from const value:
    double const val = 3.0;
    semd<double> s1(10, 3.0);

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
}

void testSemdFromSize()
{
    // create semd from size:
    semd<double> s1(10);

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
}

void testSemdFromCopy()
{
    // create semd from initializer list:
    semd<double> s1 = {1, 2, 3, 4, 5, 6, 7};
    auto const s1_cpy(s1);
    std::cout << "see copy:\n";
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1_cpy[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1_cpy.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
    std::cout << "see original:\n";
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
}

void testSemdFromMove()
{
    // create semd from initializer list:
    semd<double> s1 = {1, 2, 3, 4, 5, 6, 7};
    auto const s1_moved(std::move(s1));
    std::cout << "see copy:\n";
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1_moved[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1_moved.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
    std::cout << "see original:\n";

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
}

void testSemdCopyAssign()
{
    // create semd from initializer list:
    semd<double> s1 = {1, 2, 3, 4, 5, 6, 7};
    auto const s1_cpy = s1;
    std::cout << "see copy:\n";
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1_cpy[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1_cpy.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
    std::cout << "see original:\n";

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
}

void testSemdMoveAssign()
{
    // create semd from initializer list:
    semd<double> s1 = {1, 2, 3, 4, 5, 6, 7};
    auto const s1_mv = std::move(s1);
    std::cout << "see copy:\n";
    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1_mv[t] << ", ";
    }
    std::cout << "\n";
    std::cout << "Check the alignment: \n";
    auto const p_data = s1_mv.data();
    if (((uintptr_t)p_data & 0xf) == 0)
    {
        std::cout << "Aligned address:\n";
        std::cout << "address: " << p_data << "\n";
    }
    std::cout << "see original:\n";

    for (std::size_t t = 0; t < s1.size(); ++t)
    {
        std::cout << s1[t] << ", ";
    }
    std::cout << "\n";
}

#endif ///_SEMD_T_H_
