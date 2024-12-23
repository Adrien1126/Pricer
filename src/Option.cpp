#include "../include/Option.h"

Option::Option(double spot, double strike, double maturity, double rate, double volatility, bool isCall)
    : spot(spot), strike(strike), maturity(maturity), rate(rate), volatility(volatility), isCall(isCall) {}

double Option::getSpot() const {
    return spot;
}

double Option::getStrike() const {
    return strike;
}

double Option::getMaturity() const {
    return maturity;
}

double Option::getRate() const {
    return rate;
}

double Option::getVolatility() const {
    return volatility;
}

bool Option::getIsCall() const {
    return isCall;
}
