# options-pricing
The repository prices European-style options with Monte Carlo simulation.

## Usage
At the moment the pricing-engine only works for Vanilla and Asia (Average). Below is a short guide on using CMake to obtain the executable.
1. Run ```cmake -S . -B ./build``` from the ```options-pricing/``` directory
2. From the ```options-pricing/build/``` directory run ```make```. This will output a binary file ```price```.

The engine is preset to pricing a call option with $S_0 = 100$, $K=110$, $T=1.0$, $r=0.05$, $\sigma  = 0.2$. Moreover, the number of paths for the Monte Carlo simulation is preset to $10^4$ and the number of steps is preset to $252$ (number of trading days per year).
The user may input dersired values using the avaliable flags
```
--style     // <asian/vanilla> (For now this must be the first flag)
--type      // <put/call>
--S0        // Initial underlying asset value
--K         // Strike price
--T         // Time to maturity
--r         // Risk-free interest rate
--sigma     // Volatility
--paths     // Number of paths in Monte Carlo Simulation
--steps     // Number of steps per path
--seed      // Set the seed for reproducible results
```

Usage Example:
From the ```options-pricing/``` directory,
```
$ ./build/price --style vanilla --type put --K 100 --S0 110 --T 2.0 --paths 100000 
----------------------------- 
Price:          4.04856
----------------------------- 
BS-Price:       4.07388
AbsErr:         0.0253224
----------------------------- 
RelErr:         0.653401 %
95% CI:         [3.99671, 4.10041]
Paths:          100000

$ ./build/price --style asian --type call --K 100 --S0 110 --T 1.0 --r 0.06 --sigma 0.3
----------------------------- 
Price:          14.8057
----------------------------- 
RelErr:         1.08479 %
95% CI:         [14.4909, 15.1205]
Paths:          10000
```



## Basic Theory - under construction
### Black-Scholes Model - General Pricing Formula
Famously, Black, Scholes and Merton derived a general pricing formula for European-style options. The model considers a portfolio consisting of a risk-free asset and a risky asset. The risk-free asset (i.e. treasury bonds, or money markets) $\{B_t, 0\leq t\leq T\}$, with constant risk-free (interest) rate $r>0$, is modelled by the deterministic differential equation
$$dB_t = r\, B_t\, dt, \qquad B_0 = 1.$$
whose solution is given by $B_t = \exp(rT)$. The risky asset is a non-dividend paying stock with price process $\{S_t, 0\leq t \leq T\}$ which follows a geometric Brownian motion, that is, 
$$dS_t = \mu \, S_t\, dt + \sigma \, S_t \, dW_t, \qquad S_0 > 0. $$

where $\mu > 0$ is the drift rate, $\sigma >0$ is the volatility, and $\{W_t, 0\leq t \leq T\}$ is a Weiner process.

Under the additional assumptions ... . The gerneral pricing formula
$$V_t = \mathbb{E}_{\mathbb{Q}}[B_T^{-1}C_T | \mathcal{F}_t], \qquad 0\leq t \leq T.$$

In the case of European vanilla options analytic solution known as the Black-Scholes formula exists. However, for many other European-style options no closed-form solutions exist, and so we turn to numerical approximations. 

### Pricing via Monte Carlo Simulation




