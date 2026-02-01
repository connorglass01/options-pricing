#include "../include/pricing/types.h"
#include "../include/pricing/engines.h"
#include "../include/rng/Random.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>

/*PriceResult vanilla_closed_form(const MarketData&, const Vanilla&)
{

}*/

PriceResult vanilla_mc(const MarketData& data, const Vanilla& option, const MCSettings& settings)
{
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

    double payoff_sum {};

    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (std::size_t i {}; i < settings.numPaths; ++i)
    {
        // Realisation of the Weiner process {Z_t, 0 <= t <= T}
        double Z_T { };
        for (std::size_t j { 1 }; j < settings.numSteps; ++j)
        {
            Z_T += norm_dist(Random::mt);
        }

        const double S_T = data.S0 * std::exp(drift + data.sigma * Z_T);

        payoff_sum +=  payoff(S_T);
    }

    // Return the Monte Carlo estimator

    PriceResult result;
    result.price = disc * payoff_sum / static_cast<double>(settings.numPaths);
    result.relErr = 0.0; 
    result.ciLow = 0.0;
    result.ciHigh = 0.0;
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


    double Xi_sum {};

    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (std::size_t i {}; i < settings.numPaths; ++i)
    {
        
        double path { data.S0 };
        double sum_S { 0.0 };

        for (std::size_t j { }; j < settings.numSteps; ++j)
        {
            path *= std::exp(drift + data.sigma * norm_dist(Random::mt));  // Cumprod step
            sum_S += path; // Keeping track of the price
        }
        double avgPath { sum_S / static_cast<double>(settings.numSteps) }; // averaging the price
        Xi_sum += disc * payoff(avgPath); // Applying discounting to simulation result
    }

    PriceResult result;
    result.price = Xi_sum / static_cast<double>(settings.numPaths);
    result.relErr = 0.0; 
    result.ciLow = 0.0;
    result.ciHigh = 0.0;
    result.numPaths = settings.numPaths;
    
    return result; 
}