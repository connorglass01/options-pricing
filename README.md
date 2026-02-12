# options-pricing
This repository implements a C++ pricing engine for European-style options via Monte Carlo Simulation. In addition to the price, the engine provides
relative error and CI calculations.

The project is designed as a CLI with reproducible results with seeding. Moreover, it served as an opportunity to learn about Monte Carlo Simulation and its application to financial mathematics.

## Features 
- Monte Carlo pricing for: 
    - Vanilla European (put/call) options
    - Asian (Average) (put/call) options
- Analytic Black-Scholes pricing for Vanilla options
    - Absolute error of MC pricing for Vanilla options
- 95% Confidence Interval for MC pricing
- Reproducible simulation via RNG seeding
- Command-line interface (CLI)
- Modular C++ design

## Build Instructions (CMake)
In what follows, it is assumed the user has [CMake](https://cmake.org/) installed and note that the minimum required version of CMake is set to Version 4.2.1.

From the project root: 
```bash
cmake -S . -B ./build
cmake -B ./build
```
This process produces the executable:
```bash
./build/price
```
## Usage
### Default Parameters
As previously mentioned, the intention of this project is a CLI pricing engine. However, if no parameters are provided via flags the engine prices all options with the default parameters: 

| Parameter | Value |
|:---:|:---:|
| Spot $S_0$ | 100 |
| Strike $K$ | 110 |
|   Maturity $T$ | 1.0|
| Risk-free rate $r$ | 0.05 |
| Volatility $\sigma$ | 0.2 |
| MC Paths | 10000  |
| MC Steps | $T \times 252$

All of the parameters can be overridden via CLI flags. 

### CLI Flags
The application requires, at the very least, a specification of the option style, that is,
```bash
./build/price <vanilla | asian>
```
in which case the default parameters are used. To override any or all of the parameters append the desired flag followed a the chosen value. 

```
--type      // <put | call>
--S0        // Initial underlying asset value
--K         // Strike price
--T         // Time to maturity
--r         // Risk-free interest rate
--sigma     // Volatility
--paths     // Number of paths in Monte Carlo Simulation
--steps     // Number of steps per path
--seed      // Set the seed for reproducible results
```
Finally, the ```--help``` flag can be appended to provide a usage summary.
```
./build/price --help
```
### Usage Examples
Vanilla European options provides Monte Carlo pricing and Black-Scholes.
```
./build/price vanilla --type call --S0 100 --K 100 --T 1.0 --r 0.05 --sigma 0.2 --paths 2000000 --seed 42
```
Output: 
```
----------------------------------- 
Price:          10.4337
----------------------------------- 
BS-Price:       10.4506
AbsErr:         0.0168592
----------------------------------- 
RelErr:         0.0995909%
95% CI:         [10.4134, 10.4541]
Paths:          2000000
```
- Price: Monte Carlo estimate
- BS-Price: Analytic Black-Scholes price
- 95% CI: Confidence interval based on Monte Carlo standard error

For Asian (Average) options the Monte Carlo pricing is provided.
```
./build/price asian --type call --S0 40 --K 35 --T 0.33 --r 0.07 --sigma 0.2 --steps 88
```
Output:
```
----------------------------------- 
Price:          5.37515
----------------------------------- 
RelErr:         0.484718%
95% CI:         [5.32408, 5.42621]
Paths:          10000
```

## Numerical Methods
### Pseudo-Random Number Generation
Simulations use the Mersenne Twister PRNG (```std::mt19937```) from the C++ ```<random>``` header. Normally distributed samples are generated via ```std::normal_distribution```.

### Asset Dynamics Framework
The underlying asset dynamics follow

$$dS_t = \mu \,S_t\,dt + \sigma \,S_t \,d W_t$$

where $W_t$ denotes a Wiener process under the real measure. The assumptions of the Black-Scholes model imply the vaule of a European style option at time $t\leq T$ is given by 
$$V_t = B_t\mathbb{E}_\mathbb{Q}[B_T^{-1}V_T|\mathcal{F}_t]$$
where $\mathbb{Q}$ denotes the risk-neutral measure.
### Implementation Statistical Analysis
Monte Carlo sample variance is computed via Welford's Online algorithm is implemented. The relative error is calculated using the sample variance and confidence intervals use the asymptotically normal approximation. 

### Example Convergence Study
The following study was performed on an Apple M1 Chip. The tabulated results below presents prices vanilla European call options using Monte Carlo simulation with a varied number of paths. The seed was set to 42.
| Paths | Price (4S.F.) |AbsErr (4S.F.)| RelErr (3 S.F.) | (Real) Time | 
|:---:|:---:|:---:|:---:|:---:|
|1e4|6.088|0.0485|1.94%| 0m0.069s|
|1e5|6.013|0.0261|0.608%| 0m0.442s|
|1e6|6.012|0.0274|0.192%|0m4.144s|
|1e7|6.021 |0.0190 |0.060% |0m41.456s|
## Future Extension
Possible future features: 
- ```--greek <bool>``` which determines the Greeks for the specified option using finite difference methods and Monte Carlo estimators
- Other Exotic options, such as Barrier options
- Implied Volatility solver 

## References
- Kroese, Taimre, Botev, *Handbook of Monte Carlo Methods*

