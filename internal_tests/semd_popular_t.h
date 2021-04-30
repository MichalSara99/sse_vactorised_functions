#if !defined(_SEMD_POPULAR_T_H_)
#define _SEMD_POPULAR_T_H_

#include "internal_tests/semd_distributions_t.h"
#include "semd/semd_distributions.h"
#include <chrono>
#include <iostream>
#include <random>

template <typename fp_type>
std::vector<fp_type> const stock_price(fp_type init, fp_type rate, fp_type vol, fp_type time, std::size_t size)
{
    std::vector<fp_type> rs(size);
    std::normal_distribution<fp_type> norm(0.0, 1.0);
    std::default_random_engine eng;
    fp_type sq = std::sqrt(time);
    fp_type drift = (rate - static_cast<fp_type>(0.5) * vol * vol) * time;
    for (std::size_t i = 0; i < size; ++i)
    {
        rs[i] = init * exp(drift) * std::exp(vol * sq * norm(eng));
    }
    return rs;
}

template <typename fp_type>
void blackScholesCallPrice(semd<fp_type> const &stock, semd<fp_type> const &strike, semd<fp_type> const &rate,
                           semd<fp_type> const &vol, semd<fp_type> const &mat, semd<fp_type> &price)
{
    const semd<fp_type> d_1 =
        (semd_functions::log(stock / strike) + (rate + static_cast<fp_type>(0.5) * vol * vol) * mat) /
        (vol * semd_functions::sqrt(mat));
    const semd<fp_type> d_2 = d_1 - vol * semd_functions::sqrt(mat);
    price = stock * semd_distributions::normal::cdf(d_1) -
            strike * semd_functions::exp(-rate * mat) * semd_distributions::normal::cdf(d_2);
}

template <typename fp_type>
void blackScholesPutPrice(semd<fp_type> const &stock, semd<fp_type> const &strike, semd<fp_type> const &rate,
                          semd<fp_type> const &vol, semd<fp_type> const &mat, semd<fp_type> &price)
{
    const semd<fp_type> d_1 =
        (semd_functions::log(stock / strike) + (rate + static_cast<fp_type>(0.5) * vol * vol) * mat) /
        (vol * semd_functions::sqrt(mat));
    const semd<fp_type> d_2 = d_1 - vol * semd_functions::sqrt(mat);
    price = strike * semd_functions::exp(-rate * mat) * semd_distributions::normal::cdf(-d_2) -
            stock * semd_distributions::normal::cdf(-d_1);
}

template <typename fp_type>
fp_type blackScholesCallPrice(fp_type const stock, fp_type const strike, fp_type const rate, fp_type const vol,
                              fp_type const mat)
{
    const fp_type d_1 =
        (std::log(stock / strike) + (rate + static_cast<fp_type>(0.5) * vol * vol) * mat) / (vol * std::sqrt(mat));
    const fp_type d_2 = d_1 - vol * std::sqrt(mat);
    return (stock * norm_cdf(d_1) - strike * std::exp(-rate * mat) * norm_cdf(d_2));
}

template <typename fp_type>
fp_type blackScholesPutPrice(fp_type const stock, fp_type const strike, fp_type const rate, fp_type const vol,
                             fp_type const mat)
{
    const fp_type d_1 =
        (std::log(stock / strike) + (rate + static_cast<fp_type>(0.5) * vol * vol) * mat) / (vol * std::sqrt(mat));
    const fp_type d_2 = d_1 - vol * std::sqrt(mat);
    return (strike * std::exp(-rate * mat) * norm_cdf(-d_2) - stock * norm_cdf(-d_1));
}

template <typename fp_type> void testBlackScholesPrice()
{
    std::size_t const n = 1000000;
    std::vector<fp_type> const rate(n, static_cast<fp_type>(0.001));
    std::vector<fp_type> const vol(n, static_cast<fp_type>(0.025));
    std::vector<fp_type> const time(n, static_cast<fp_type>(1.0));
    std::vector<fp_type> const strike_call(n, static_cast<fp_type>(103.5));
    std::vector<fp_type> const strike_put(n, static_cast<fp_type>(98.5));
    fp_type const init(100.5);
    const std::vector<fp_type> stock = stock_price<fp_type>(init, rate.front(), vol.front(), time.front(), n);
    //#define _SEE_OUTPUT_
    const semd<fp_type> rate_semd(rate);
    const semd<fp_type> vol_semd(vol);
    const semd<fp_type> time_semd(time);
    const semd<fp_type> strike_call_semd(strike_call);
    const semd<fp_type> strike_put_semd(strike_put);
    const semd<fp_type> stock_semd(stock);
    semd<fp_type> call(n);
    std::vector<fp_type> call_cpp(n);
    semd<fp_type> put(n);
    std::vector<fp_type> put_cpp(n);

    auto start_semd = std::chrono::steady_clock::now();
    blackScholesCallPrice<fp_type>(stock_semd, strike_call_semd, rate_semd, vol_semd, time_semd, call);
    auto end_semd = std::chrono::steady_clock::now();
    auto elapsed_semd = std::chrono::duration_cast<std::chrono::milliseconds>(end_semd - start_semd).count();

    auto start_cpp = std::chrono::steady_clock::now();
    for (std::size_t t = 0; t < n; ++t)
    {
        call_cpp[t] = blackScholesCallPrice<fp_type>(stock[t], strike_call[t], rate[t], vol[t], time[t]);
    }
    auto end_cpp = std::chrono::steady_clock::now();
    auto elapsed_cpp = std::chrono::duration_cast<std::chrono::milliseconds>(end_cpp - start_cpp).count();

#ifdef _SEE_OUTPUT_
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cout << i << ": " << call_cpp[i] << " | " << call[i] << " || " << (call_cpp[i] - call[i]) << "\n";
    }
#endif

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "====================== CALL ===========================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp << " milliseconds";
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << " milliseconds"
              << "\n";

    start_semd = std::chrono::steady_clock::now();
    blackScholesPutPrice<fp_type>(stock_semd, strike_put_semd, rate_semd, vol_semd, time_semd, put);
    end_semd = std::chrono::steady_clock::now();
    elapsed_semd = std::chrono::duration_cast<std::chrono::milliseconds>(end_semd - start_semd).count();

    start_cpp = std::chrono::steady_clock::now();
    for (std::size_t t = 0; t < n; ++t)
    {
        put_cpp[t] = blackScholesPutPrice<fp_type>(stock[t], strike_put[t], rate[t], vol[t], time[t]);
    }
    end_cpp = std::chrono::steady_clock::now();
    elapsed_cpp = std::chrono::duration_cast<std::chrono::milliseconds>(end_cpp - start_cpp).count();

#ifdef _SEE_OUTPUT_
    for (std::size_t i = 0; i < n; ++i)
    {
        std::cout << i << ": " << put_cpp[i] << " | " << put[i] << " || " << (put_cpp[i] - put[i]) << "\n";
    }
#endif

    std::cout << "\n";
    std::cout << "\n";
    std::cout << "====================== PUT ===========================\n\n";
    std::cout << "\n"
              << "Elapsed (C++): " << elapsed_cpp << " milliseconds";
    std::cout << "\n"
              << "Elapsed (Semd): " << elapsed_semd << " milliseconds"
              << "\n";
}

#endif ///_SEMD_POPULAR_T_H_
