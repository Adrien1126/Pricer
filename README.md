# Pricer
This repository allows to price European and American option

## Binomial model 

In our work, we assume that :
- The price of the underlying instrument is a geometric Brownian motion with constant drift and volatility
- It is possible to short sell the underlying stock r There are no riskless arbitrage opportunities
- Trading in the stock is continuous
- There are no transaction costs
- All securities are perfectly divisible (e.g. it is possible to buy 1/100th of a share)
- The risk free interest rate is constant, and it has the same value for all maturity dates

We assume that no dividends are paids. 

We are mainly interested in pricing one-factor European call and put options based on a single asset S whose values change according to the stochastic differential equation given by : 

$$
dS=\mu S dt + \sigma S dW
$$
