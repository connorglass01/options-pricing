#include "../include/pricing/types.h"
#include "../include/pricing/engines.h"
#include "../include/rng/Random.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>

double normalCDF(double x)
{
    return std::erfc( -x / std::sqrt(2)) / 2;
}

double d1(const MarketData& data, const Vanilla& option)
{
    return (std::log(data.S0/option.K) + (data.r + data.sigma * data.sigma * 0.5) * option.T)
     / (data.sigma * std::sqrt(option.T));
}

double d2(const MarketData& data, const Vanilla& option)
{
    return d1(data, option) - data.sigma * std::sqrt(option.T);
}

double bsPrice(const MarketData& data, const Vanilla& option)
{
    const double d1v { d1(data, option) };
    const double d2v {d2(data, option)};
    const double disc { std::exp(-data.r * option.T) };

    if (option.type == OptionType::call)
    {
        return data.S0 * normalCDF(d1v) - option.K * disc * normalCDF(d2v);
    }
    else if (option.type == OptionType::put)
    {
        return option.K * disc * normalCDF(-d2v) - data.S0 * normalCDF(-d1v);
    }
    
    std::cerr << "optionType must be \"call\" or \"put\" ";
    return 1;
    
}


PriceResult vanilla_mc(const MarketData& data, const Vanilla& option, const MCSettings& settings)
{
    // Monte Carlo Pricing
    auto payoff{
        [ option ]( double S_T )
        {
            if (option.type == OptionType::call)
                return std::max(S_T - option.K, 0.0);
            else
                return std::max(option.K - S_T, 0.0);
        }
    };

    const double dt { option.T / settings.numSteps };
    const double drift { (data.r - 0.5 * data.sigma * data.sigma) * option.T } ;
    const double disc { std::exp(-data.r * option.T) };


    // Welford's Algo for Variance - Initialising Variables
    std::size_t n {};
    double mean {};
    double M2 {};

    double payoff_sum {};

    std::mt19937 rng = Random::generate(settings.seed);
    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (std::size_t i {}; i < settings.numPaths; ++i)
    {
        // Realisation of the Weiner process {Z_t, 0 <= t <= T}
        double Z_T { };
        for (std::size_t j { 1 }; j < settings.numSteps; ++j)
        {
            Z_T += norm_dist(rng);
        }

        const double S_T = data.S0 * std::exp(drift + data.sigma * Z_T);

        double discPayoff {disc * payoff(S_T)};

        ++n;
        double delta { discPayoff - mean };
        mean += delta / static_cast<double>(n);
        M2 += delta * (discPayoff - mean);

        payoff_sum +=  payoff(S_T);
    }


    // Processing Welfords Algo
    double payoffVar { (n > 1) ? M2 / static_cast<double>(n - 1) : 0.0 };
    double payoffStd { std::sqrt(payoffVar) };
    double width {(payoffStd * 1.96) / std::sqrt(static_cast<double>(n))};

    // Return the Monte Carlo estimator
    PriceResult result;
    result.price = disc * payoff_sum / static_cast<double>(settings.numPaths);
    result.analyticalPrice = bsPrice(data,option);
    result.relErr = payoffStd /( mean * std::sqrt(static_cast<double>(n))); 
    result.ciLow = mean - width;
    result.ciHigh = mean + width;
    result.numPaths = settings.numPaths;

    return result;
}


PriceResult asian_mc(const MarketData& data, const Asian& option, const MCSettings& settings)
{
    auto payoff{
        [ option ]( double A_T )
        {
            if (option.type == OptionType::call)
                return std::max(A_T - option.K, 0.0);
            else
                return std::max(option.K - A_T, 0.0);
        }
    };

    const double dt { option.T / settings.numSteps };
    const double drift { (data.r - 0.5 * data.sigma * data.sigma) * dt } ;
    const double disc { std::exp(-data.r * option.T) };

    // Welford's Algo for Variance - Initialising Variables
    std::size_t n {};
    double mean {};
    double M2 {};


    //double Xi_sum {};

    std::mt19937 rng = Random::generate(settings.seed);
    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (std::size_t i {}; i < settings.numPaths; ++i)
    {
        
        double path { data.S0 };
        double sum_S { 0.0 };

        for (std::size_t j { }; j < settings.numSteps; ++j)
        {
            //path *= std::exp(drift + data.sigma * norm_dist(Random::mt));  // Cumprod step
            path *= std::exp(drift + data.sigma * norm_dist(rng)); 
            sum_S += path; // Keeping track of the price
        }
        double avgPath { sum_S / static_cast<double>(settings.numSteps) }; // averaging the price
        double discPayoff {disc * payoff(avgPath)};

        //Xi_sum += discPayoff; // Applying discounting to simulation result
        
        ++n;
        double delta { discPayoff - mean };
        mean += delta / static_cast<double>(n);
        M2 += delta * (discPayoff - mean);
    }


    // Processing Welfords Algo
    double payoffVar { (n > 1) ? M2 / static_cast<double>(n - 1) : 0.0 };
    double payoffStd { std::sqrt(payoffVar) };
    double width {(payoffStd * 1.96) / std::sqrt(static_cast<double>(n))};
    PriceResult result;
    result.price = mean;
    result.relErr = payoffStd /( mean * std::sqrt(static_cast<double>(n))); 
    result.ciLow = mean - width;
    result.ciHigh = mean + width;
    result.numPaths = settings.numPaths;
    
    return result; 
}