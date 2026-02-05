#ifndef TYPES_H
#define TYPES_H

#include <optional>
#include <cstdlib>

namespace Constants
{
    inline constexpr int tradingDaysMonth { 22 };
    inline constexpr int tradingDaysYear { 252 };
}


enum OptionType 
{
    call, 
    put,
};

struct MarketData
{
    double S0 { 100.0 };      // Initial value of the underlying stock
    double r { 0.05 };      // Risk-free interest rate
    double sigma { 0.2 };      // 
};

struct Vanilla
{
  double K { 110.0 }; 
  double T { 1.0 };
  OptionType type { OptionType::call };
};

struct Asian
{
    double K { 110.0 }; 
    double T { 1.0 };
    OptionType type { OptionType::call };
};


struct MCSettings
{  
    std::optional<u_int64_t> seed; 
    std::size_t numPaths { 10000 };
    std::size_t numSteps { Constants::tradingDaysYear };
};

struct PriceResult
{
    double price {};
    double analyticalPrice {};
    double relErr {};
    double ciLow {};
    double ciHigh {};
    std::size_t numPaths {};
};


struct PriceResultVanilla
{
    double price {};
    double analyticalPrice {};
    double relErr {};
    double ciLow {};
    double ciHigh {};
    std::size_t numPaths {};
};


#endif