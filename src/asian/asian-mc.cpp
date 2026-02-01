#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <string>
#include <numeric>

#include "../../include/rng/Random.h"

double monte_carlo_price(double S, double K, double T, double r, double sigma,
    int time_steps, int num_paths, std::string_view optionType)
{

    auto payoff{
        [K, optionType]( double avgS_T )
        {
            if (optionType == "call")
                return std::max(avgS_T - K, 0.0);
            else
                return std::max(K - avgS_T, 0.0);
        }
    };

    const double dt { T/time_steps };
    const double drift { (r - 0.5 * sigma * sigma) * dt } ;
    const double disc { std::exp(-r * T) };

    double Xi_sum {};

    std::normal_distribution norm_dist {0.0, std::sqrt(dt)};

    for (int i {}; i < num_paths; ++i)
    {
        
        double path { S };
        double sum_S { 0.0 };

        for (int j { }; j < time_steps; ++j)
        {
            path *= std::exp(drift + sigma * norm_dist(Random::mt));  // Cumprod step
            sum_S += path; // Keeping track of the price
        }
        double avgPath { sum_S / static_cast<double>(time_steps) }; // averaging the price
        Xi_sum += disc * payoff(avgPath); // Applying discounting to simulation result
    }

    // Return the Monte Carlo estimator
    return Xi_sum / static_cast<double>(num_paths);
}


int main()
{
    std::cout << monte_carlo_price(100, 110, 1.0, 0.05, 0.2, 252, 10000, "call") << '\n';
    std::cout << monte_carlo_price(40, 35, 4.0/12.0, 0.07, 0.2, 88, 10000, "put") << '\n';
    return 0;
}
