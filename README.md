# options-pricing
The repository prices European-style options with Monte Carlo simulation.

## Usage
At the moment the pricing-engine only works for Vanilla and Asia (Average). Below is a short guide on using CMake to obtain the executable.
1. Run ```cmake -S . -B ./build``` from the ```options-pricing/``` directory
2. From the ```options-pricing/build/``` directory run ```make```. This will output a binary file ```price``.

The engine is preset to pricing a call option with $S_0 = 100$, $K=110$, $T=1.0$, $r=0.05$, $\sigma  = 0.2$. For now, to change these value the user is asked to modify ```include/pricing/types.h``` to the desired parameters.

Usage Example:
From the ```options-pricing/``` directory,
```
$ ./build/price vanilla
Price: 6.21958
Paths: 10000

$ ./build/price vanilla put
Price: 10.5859
Paths: 10000
```



## Basic Theory - under construction
### Black-Scholes Model - General Pricing Formula
Famously, Black, Scholes and Merton derived a general pricing formula for European-style options. The model considers a portfolio consisting of a risk-free asset and a risky asset. The risk-free asset (i.e. treasury bonds, or money markets) $\{B_t, 0\leq t\leq T\}$, with constant risk-free (interest) rate $r>0$, is modelled by the deterministic differential equation
$$ dB_t = r\, B_t\, dt, \qquad B_0 = 1.$$
whose solution is given by $B_t = \exp(rT)$. The risky asset is a non-dividend paying stock with price process $\{S_t, 0\leq t \leq T\}$ which follows a geometric Brownian motion, that is, 
$$dS_t = \mu \, S_t\, dt + \sigma \, S_t \, dW_t, \qquad S_0 > 0. $$

where $\mu > 0$ is the drift rate, $\sigma >0$ is the volatility, and $\{W_t, 0\leq t \leq T\}$ is a Weiner process.

Under the additional assumptions ... . The gerneral pricing formula
$$ V_t = \mathbb{E}_{\mathbb{Q}}[B_T^{-1}C_T | \mathcal{F}_t], \qquad 0\leq t \leq T.$$

In the case of European vanilla options analytic solution known as the Black-Scholes formula exists. However, for many other European-style options no closed-form solutions exist, and so we turn to numerical approximations. 

### Pricing via Monte Carlo Simulation




