#include "../include/EuropeanOption.h"
#include <cmath>
#include <algorithm>
#include "../include/Utilities.h"

EuropeanOption::EuropeanOption(double spot, double strike, double maturity, double rate, double volatility, bool isCall)
    : Option(spot, strike, maturity, rate, volatility, isCall) {}

double EuropeanOption::calculateBSPrice() const {
    double d1 = (log(spot / strike) + (rate + 0.5 * volatility * volatility) * maturity) /
                (volatility * sqrt(maturity));
    double d2 = d1 - volatility * sqrt(maturity);

    if (isCall) {
        return spot * norm_cdf(d1) - strike * exp(-rate * maturity) * norm_cdf(d2);
    } else {
        return strike * exp(-rate * maturity) * norm_cdf(-d2) - spot * norm_cdf(-d1);
    }
}
