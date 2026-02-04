#include <iostream>

#include "../include/pricing/types.h"
#include "../include/cli/cli.h"

double parseDouble(std::string str_Double, const std::string name)
{
    std::size_t idx = 0;

    double val = std::stod(str_Double, &idx);
    if (idx != str_Double.size())
    {
        throw std::runtime_error("Invalid " + name + " value: '" + str_Double + "'");
    }

    return val;
}


CLIArgs parseArgs(int argc, char* argv[])
{

    CLIArgs userArgs;

    // Starting at 3 bc the first are reserved for ./price <optionstyle>
    for (int i {3}; i < argc; ++i)
    {
        std::string_view arg { argv[i] };

        if (arg == "--type")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Type <put/call> missing after" + std::string(arg));
            }
            std::string_view option_type { argv[++i] };
            
            if (option_type == "put" || option_type == "Put")
            {
                userArgs.type = OptionType::put;
            }
            else if (option_type == "call" || option_type == "Call")
            {
                userArgs.type = OptionType::call;
            }
        }
        else if (arg == "--S0")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("S0 value missing after" + std::string(arg));
            }

            const std::string name { "S0" };
            std::string str_S0 { argv[++i] };

            userArgs.S0 = parseDouble(str_S0, name);
        }
        else if (arg == "--K")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("K value missing after" + std::string(arg));
            }

            const std::string name { "K" };
            std::string str_K { argv[++i] };

            userArgs.K = parseDouble(str_K, name);
        }
        else if (arg == "--r")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("r value missing after" + std::string(arg));
            }

            const std::string name { "r" };
            std::string str_r { argv[++i] };

            userArgs.r = parseDouble(str_r, name);
        }
        else if (arg == "--sigma")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Sigma value missing after" + std::string(arg));
            }

            const std::string name { "Sigma" };
            std::string str_sigma { argv[++i] };

            userArgs.sigma = parseDouble(str_sigma, name);
        }
        else if (arg == "--T")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("T value missing after" + std::string(arg));
            }

            const std::string name { "T" };
            std::string str_T { argv[++i] };

            userArgs.T = parseDouble(str_T, name);
        }
        else if (arg == "--paths")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("T value missing after" + std::string(arg));
            }

            const std::string name { "Paths" };
            std::string str_paths { argv[++i] };

            userArgs.numPaths = parseDouble(str_paths, name);
        }
        else if (arg == "--steps")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("T value missing after" + std::string(arg));
            }

            const std::string name { "steps" };
            std::string str_steps { argv[++i] };

            userArgs.numSteps = parseDouble(str_steps, name);
        }
    }

    return userArgs;
}