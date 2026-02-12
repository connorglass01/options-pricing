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
    for (int i {2}; i < argc; ++i)
    {
        std::string_view arg { argv[i] };

        if (arg == "--type")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Option type <put/call> missing after " + std::string(arg));
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
                throw std::runtime_error("Underlying asset initial value (S0) missing after " + std::string(arg));
            }

            const std::string name { "S0" };
            std::string str_S0 { argv[++i] };

            userArgs.S0 = parseDouble(str_S0, name);
        }
        else if (arg == "--K")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Strike price (K) value missing after " + std::string(arg));
            }

            const std::string name { "K" };
            std::string str_K { argv[++i] };

            userArgs.K = parseDouble(str_K, name);
        }
        else if (arg == "--r")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Risk-free interest rate (r) value missing after " + std::string(arg));
            }

            const std::string name { "r" };
            std::string str_r { argv[++i] };

            userArgs.r = parseDouble(str_r, name);
        }
        else if (arg == "--sigma")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Volatility (sigma) value missing after " + std::string(arg));
            }

            const std::string name { "Sigma" };
            std::string str_sigma { argv[++i] };

            userArgs.sigma = parseDouble(str_sigma, name);
        }
        else if (arg == "--T")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Time to maturity (T) value missing after " + std::string(arg));
            }

            const std::string name { "T" };
            std::string str_T { argv[++i] };

            userArgs.T = parseDouble(str_T, name);
        }
        else if (arg == "--paths")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Number of paths value missing after " + std::string(arg));
            }

            const std::string name { "Paths" };
            std::string str_paths { argv[++i] };

            userArgs.numPaths = parseDouble(str_paths, name);
        }
        else if (arg == "--steps")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("Number of steps per path value missing after " + std::string(arg));
            }

            const std::string name { "steps" };
            std::string str_steps { argv[++i] };

            userArgs.numSteps = parseDouble(str_steps, name);
        }
        else if (arg == "--seed")
        {
            if (i + 1 >= argc)
            {
                throw std::runtime_error("PRNG seed value missing after " + std::string(arg));
            }

            const std::string name { "seed" };
            std::string str_seed { argv[++i] };

            userArgs.seed = parseDouble(str_seed, name);
        }
        else if (arg == "--help")
        {
            userArgs.help = true;
        }
    }
    return userArgs;
}



void help_msg()
{
    std::cout << "Usage:\n";
    std::cout << "----------\n";
    std::cout << "Specify the option style and run the exectuable via\n";
    std::cout << "./build/price <vanilla|asian>\n\n";
    std::cout << "Optional Flags:\n";
    std::cout << "------------------\n";
    std::cout << "--type <call|put>\n--S0 <float>\n--K <float>\n--T <float>\n--r <float>\n--sigma <float>\n";
    std::cout << "--paths <int>\n--seed <int>\n--steps <int>\n[--help] \n\n";
    std::cout << "Examples: \n";
    std::cout << "----------\n";
    std::cout << "./build/price vanilla --type call --S0 100 --K 100 --T 1.0 --r 0.05 --sigma 0.2 --paths 2000000 --seed 42\n";
    std::cout << "./build/price asian --type call --S0 40 --K 35 --T 0.33 --r 0.07 --sigma 0.2 --steps 88\n";
}