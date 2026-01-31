# options-pricing

*** write summary ***


## Features


## Theory

### The Black-Scholes(-Merton) Model

*** NEED TO MAKE SURE THE FILTRATION IS CONSISTENT ***

In this section we provide a brief summary of the Black-Scholes model. We assume familiarity with common notions in probability theory to the level of an typical graduate level course.
In what follows, let $(\Omega, \mathcal{F}, \mathbb{P})$ be a filtered probability space, with respect to the filtration $\{\mathcal{F}_t, t\geq 0\}$. It is common to refer to $\mathbb{P}$ as the "physical" probability measure.

DESCRIBE WHAT THE BLACK-SCHOLES MODEL DOES

We consider a portfolio consisting of two assets. The first, a risk-free asset (i.e. treasury bonds, or money market) $\{B_t, 0\leq t\leq T\}$, with constant risk-free (interest) rate $r>0$. The risk-free asset is modelled by the deterministic differential equation
$$
dB_t = r \,B_t\,dt, \qquad B_0 = 1.
$$
Of course, 
$$
B_t = \exp\left(rT\right)
$$

The second, a risky-asset given by a non-dividend paying stock with price process $\{S_t, 0\leq t\leq T\}$ which follows a geometric Brownian motion given by the stochastic differential equation
$$
dS_t = \mu \, S_t\, dt + \sigma \, S_t \, dW_t, \qquad S_0 > 0.
$$
where $\mu > 0$ is the drift rate, $\sigma >0$ is the volatility, and $\{W_t, 0\leq t \leq T\}$ is a Weiner process under $\mathbb{P}$.


***The First Fundamental Theorem of Asset Pricing*** A market is arbitrage-free, if and only if, there exists an equivalent measure $\mathbb{Q}$ such that the discounted asset price process $\{B_t^{-1}S_t\}$ is a $(\{\mathcal{F}_t\}, \mathbb{Q})$-martingale, that is to say, there exists a risk-neutral probability measure $\mathbb{Q}$.

A market is said to be complete if FINISH THIS ******


***The Second Fundamental Theorem of Asset Pricing*** A market is complete if and only if the risk-neutral measure is unique. 

*** STATE ASSUPTIONS AND HOW WE THEN GET THE FORMULA FOR BELOW ***

Derive up to 
$$
V_t = B_t \mathbb{E}_{\mathbb{Q}}[B_T^{-1} V_T | \mathcal{F}_t], \qquad t \leq T.
$$

For the majority of the options in TABLE, there is no closed for solution to the expression above. Hence, one uses Monte Carlo simulations to approximate the price using the equation above.

### Pricing via Monte Carlo Simulation




#### Example: European Style Asian (Average) Options
Consider the European style Asian call option with maturity $T$ and strike price $K$.
The pay-off function at maturity is of the form
$$
C_T = (A_T - K)^+
$$
where $A_t$ denotes the average price of the underlying asset over the interval $[0,t]$, viz.
$$
A_t = \frac{1}{t}\int_0^t S_u \, ds, \quad t\in [0,T].
$$

Thus, under the Black-Scholes model described above, we assume the underlying asset is modelled by the SDE
$$
dS_t = \mu \,S_t\,dt + \sigma \,S_t\, dW_t
$$
where $\{W_t\}$ denotes a Weiner process under $\mathbb{P}$. Let $r$ denote the risk-free annual interest rate. Then by an analogous argument to above, the price of the European style Asian call option at $t\in [0,T]$, under the risk-neutral measure $\mathbb{Q}$ is given by
$$
C_t = \exp(-r(T-t))\mathbb{E}_{\mathbb{Q}}[(A_T - K)^+ | \mathcal{F}_t].
$$



