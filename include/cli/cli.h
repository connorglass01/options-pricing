#ifndef FLAGS_H
#define FLAGS_H

#include <string>
#include <cmath>
#include <optional>

#include "../pricing/types.h"

enum class OptionStyle { Vanilla, Asian };


struct CLIArgs
{
    OptionStyle style;
    OptionType type { OptionType::call };

    double S0 { 100.0 };      // Initial value of the underlying stock
    double r { 0.05 };      // Risk-free interest rate
    double sigma { 0.2 };

    double K { 110.0 }; 
    double T { 1.0 };

    std::size_t numPaths { 10000 };
    std::size_t numSteps { static_cast<std::size_t>(std::round(Constants::tradingDaysYear * T)) };

    std::optional<u_int64_t> seed;

    bool help { false };
};

CLIArgs parseArgs(int argc, char* argv[]);
std::string usage();

#endif