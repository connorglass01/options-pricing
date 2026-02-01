#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>

#include "../../include/rng/Random.h"

double monte_carlo_price(double S, double K, double T, double r, double sigma,
    int time_steps, int num_paths, std::string_view optionType)
{

    auto payoff{
        [K, optionType]( double S_T )
        {
            if (optionType == "call")
                return std::max(S_T - K, 0.0);
            else
                return std::max(K - S_T, 0.0);
        }
    };

    const double dt { T/time_steps };
    const double drift { (r - 0.5 * sigma * sigma)*T } ;
    const double disc { std::exp(-r * T) };

    double payoff_sum {};

    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (int i {}; i < num_paths; ++i)
    {
        // Realisation of the Weiner process {Z_t, 0 <= t <= T}
        double Z_T { };
        for (int j { 1 }; j < time_steps; ++j)
        {
            Z_T += norm_dist(Random::mt);
        }

        const double S_T = S * std::exp(drift + sigma * Z_T);

        payoff_sum +=  payoff(S_T);
    }

    // Return the Monte Carlo estimator
    return disc * payoff_sum / static_cast<double>(num_paths);
}


int main()
{
    std::cout <<  monte_carlo_price(100, 110, 1.0, 0.05, 0.2, 252, 100000, "call") << '\n';
    std::cout <<  monte_carlo_price(100, 90, 1.0, 0.07, 0.2, 252, 100000, "put") << '\n';
    return 0;
}
