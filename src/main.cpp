#include "../include/pricing/types.h"
#include "../include/pricing/engines.h"
#include "../include/cli/cli.h"

#include <iostream>
#include <any>
#include <string>

int main(int argc, char* argv[])
{

    CLIArgs userArgs;

    Vanilla vanilla;
    Asian asian;

    PriceResult result;
    MCSettings settings;
    MarketData data;

    // Magic Number: We require the at least ~2~ inputs
    if (argc < 2)
    {
        std::cout << "Usage: $ <program name> <option style> \n";
        return 1;
    }
    else
    {
        try
        {   // Retrieve the users desired parameters (optional)
            // See "cli.h" and "cli.cpp" for implementation
            userArgs = parseArgs(argc, argv);
        }
        catch(const std::exception& e)
        {
            // Catches errors thrown from parseArgs()
            std::cerr << e.what() << '\n';
            return 1;
        }
    }

    // Reassignment of preset values to user desired values
    data.S0 = userArgs.S0;
    data.r = userArgs.r;
    data.sigma = userArgs.sigma;

    vanilla.K = userArgs.K;
    vanilla.T = userArgs.T;
    vanilla.type = userArgs.type;

    asian.K = userArgs.K;
    asian.T = userArgs.T;
    asian.type = userArgs.type;

    settings.numPaths = userArgs.numPaths;
    settings.numSteps = userArgs.numSteps;
    settings.seed = userArgs.seed;

     
    std::string_view style { argv[1] }; 
    // Checking the option style or for the --help flag
    if (style == "--help" || userArgs.help)
    {
        help_msg();
        return 0;
    }
    if (style == "vanilla")
    {
        result = vanilla_mc(data, vanilla, settings);
    }
    else if (style == "asian")
    {
        result = asian_mc(data, asian, settings);
    }
    else
    {
        throw std::runtime_error("Invalid option style: " + std::string(style));
        return 1;
    }

    // Printing the output
    std::cout << "----------------------------------- \n"; 
    std::cout << "Price:    \t" << result.price << '\n';
    std::cout << "----------------------------------- \n";
    if (style == "vanilla")
    {
        std::cout << "BS-Price: \t" << result.analyticalPrice << '\n';
        std::cout << "AbsErr:   \t" << std::abs(result.price - result.analyticalPrice) << '\n';
        std::cout << "----------------------------------- \n"; 
    }
    std::cout << "RelErr:  \t" << result.relErr * 100 << "%\n";
    std::cout << "95% CI:   \t[" << result.ciLow << ", " << result.ciHigh << "]\n";
    std::cout << "Paths:    \t" << result.numPaths << "\n\n";
    return 0;
}
