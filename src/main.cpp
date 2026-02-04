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

    if (argc < 3)
    {
        std::cout << "Usage: $ <program name> --style <option style> \n";
        return 1;
    }

    if (argc > 3)
    {
        try
        {
            userArgs = parseArgs(argc, argv);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
    }

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

    // MAYBE REMOVE THE ---STYLE FLAG
    if (std::string(argv[1]) != "--style")
    {
        throw std::runtime_error("Usage: $ <program name> --style <option style>");
        return 1; 
    }
    else
    {
        std::string_view style { argv[2] };
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

    }
    
 

    std::cout << "Price: " << result.price << '\n';
    //std::cout << "RelErr: " << result.relErr << '\n';
    //std::cout << "CI Low: " << result.ciLow << '\n';
    //std::cout << "CI High: " << result.ciHigh << '\n';
    std::cout << "Paths: " << result.numPaths << '\n';
    return 0;
}
