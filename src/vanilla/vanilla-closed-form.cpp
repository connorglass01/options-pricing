#include <iostream>
#include <cmath>
#include <string>

double normalCDF(double x)
{
    return std::erfc( -x / std::sqrt(2)) / 2;
}

double d1(double S, double K, double T, double r, double sigma)
{
    return (std::log(S/K) + (r + sigma * sigma * 0.5) * T) / (sigma * std::sqrt(T));
}

double d2(double S, double K, double T, double r, double sigma)
{
    return d1(S, K, T, r, sigma) - sigma * std::sqrt(T);
}

double bsPrice(double S, double K, double T, double r, double sigma, std::string_view optionType)
{
    const double d1v { d1(S, K, T, r, sigma) };
    const double d2v {d2(S, K, T, r, sigma)};
    const double disc { std::exp(-r * T) };

    if (optionType == "call")
    {
        return S * normalCDF(d1v) - K * disc * normalCDF(d2v);
    }
    else if (optionType == "put")
    {
        return K * disc * normalCDF(-d2v) - S * normalCDF(-d1v);
    }
    
    std::cerr << "optionType must be \"call\" or \"put\" ";
    return 1;
    
}

int main()
{
    double C { bsPrice(100, 110, 1.0, 0.05, 0.2, "call") };
    double P { bsPrice(100, 90, 1.0, 0.07, 0.2, "put") };
    
    std::cout << C << '\n' << P << '\n';

    return 0;
}

