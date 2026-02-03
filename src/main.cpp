#include "../include/pricing/types.h"
#include "../include/pricing/engines.h"

#include <iostream>
#include <any>
#include <string>

int main(int argc, char* argv[])
{
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
            for (int i { 3 }; i < argc; ++i)
            {
                std::string_view arg {argv[i]};
                
                // This specifies the type of the option i.e. put or call
                if (arg == "--type")
                {
                    if (i + 1 >= argc)
                    {
                        throw std::runtime_error("Type <put/call> missing after" + std::string(arg));
                        return 1;
                    }
                    std::string_view option_type { argv[++i] };
                    
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
                else if (arg == "--S0")
                {
                    if (i + 1 >= argc)
                    {
                        throw std::runtime_error("S0 value missing after" + std::string(arg));
                        return 1;
                    }
                    try
                    {
                        std::string str_S0{argv[++i]};
                        std::size_t idx = 0;

                        double S0 = std::stod(str_S0, &idx);
                        if (idx != str_S0.size()) {
                            throw std::runtime_error("Invalid S0 value: '" + str_S0 + "'");
                            return 1;
                        }

                        data.S0 = S0;
                    }
                    catch(const std::invalid_argument&)
                    {
                        throw std::runtime_error("Invalid S0 (not a number)");
                        return 1;
                    }
                }
                else if (arg == "--K")
                {
                    if (i + 1 >= argc)
                    {
                        throw std::runtime_error("K value missing after" + std::string(arg));
                        return 1;
                    }
                    try
                    {
                        std::string str_K{argv[++i]};
                        std::size_t idx = 0;

                        double K = std::stod(str_K, &idx);
                        if (idx != str_K.size()) {
                            throw std::runtime_error("Invalid S0 value: '" + str_K + "'");
                            return 1;
                        }

                        vanilla.K = K;
                        asian.K = K;
                    }
                    catch(const std::invalid_argument&)
                    {
                        throw std::runtime_error("Invalid K (not a number)");
                        return 1;
                    }
                }
            
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            return 1;
        }
    }

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
