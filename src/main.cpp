#include "../include/pricing/types.h"
#include "../include/pricing/engines.h"

#include <iostream>
#include <any>
#include <string>

int main(int argc, char* argv[])
{
    Vanilla vanilla;
    Asian asian;

    if (argc < 2)
    {
        std::cout << "Usage: $ <program name> <option style> \n";
        return 1;
    }
    if (argc == 3)
    {
        const std::string option_type { argv[2] };

        if (option_type == "put" || option_type == "Put")
        {
            vanilla.type = OptionType::put;
            asian.type = OptionType::put;
        }
        else if (option_type == "call" || option_type == "Call")
        {
            vanilla.type = OptionType::call;
            asian.type = OptionType::call; 
        }
    }

    const std::string style { argv[1] };
    
    PriceResult result;
    MCSettings settings;
    MarketData data;

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
        std::cout << "Please enter a valid option style \n";
        return 1;
    }
 

    std::cout << "Price: " << result.price << '\n';
    //std::cout << "RelErr: " << result.relErr << '\n';
    //std::cout << "CI Low: " << result.ciLow << '\n';
    //std::cout << "CI High: " << result.ciHigh << '\n';
    std::cout << "Paths: " << result.numPaths << '\n';
    return 0;
}
