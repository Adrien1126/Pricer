#include "EuropeanOption.hpp"
#include <cmath>

// Implémentation de la fonction de répartition cumulative de la loi normale
double N(double x)
{
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}


void EuropeanOption::init()
{ // Initialize all default values 
    // Default values
    r_ = 0.08; 
    sigma_ = 0.30;
    K_ = 65.0;
    T_ = 0.25;
    S_ = 60.0; // U == stock in this case 
    b_ = r_; // Black and Scholes stock option model 
    optType_ = "C"; //European Call Option (the default type)
}

void EuropeanOption::copy(const EuropeanOption &o2)
{
    r_=o2.r_;
    sigma_=o2.sigma_;
    K_=o2.K_;
    T_=o2.T_;
    S_=o2.S_;
    b_=o2.b_;

    optType_=o2.optType_;
}

double EuropeanOption::callPrice() const
{
    double tmp = sigma_ *sqrt(T_);
    double d1 = (log(S_/K_)+( r_ + (sigma_*sigma_)/2)*T_)/tmp;
    double d2 = d1 - tmp;
    return S_*exp((b_-r_)*T_)* N(d1) - K_*exp(-r_*T_)* N(d2);
}

double EuropeanOption::putPrice() const
{
    double tmp = sigma_ * sqrt(T_);
    double d1 = (log(S_/K_)+(b_ + (sigma_*sigma_)/2)*T_)/tmp;
    double d2 = d1 - tmp;
    return K_*exp(-r_*T_)*N(-d2) - S_*exp((b_-r_)*T_)*N(-d1);
}

double EuropeanOption::callDeltat() const
{
    double tmp = sigma_ * sqrt(T_);
    double d1 = (log(S_/K_)+(b_ + (sigma_*sigma_)/2)*T_)/tmp;
    return exp((b_ - r_) * T_) * N(d1);
}

double EuropeanOption::putDeltat() const
{
    double tmp = sigma_ * sqrt(T_);
    double d1 = (log(S_/K_)+(b_ + (sigma_*sigma_)/2)*T_)/tmp;
    return exp((b_ - r_) * T_) * (N(d1)-1.0);
}

EuropeanOption::EuropeanOption()
{ // Default call option
    init();
}

EuropeanOption::EuropeanOption(const EuropeanOption &option2)
{
    copy(option2);
}

EuropeanOption::EuropeanOption(const string &optionType)
{ // Create option type 
    init();
    optType_=optionType;
    if (optType_ == "c")
        optType_ = "C";
}

EuropeanOption::~EuropeanOption()
{ // Destructor

}

EuropeanOption &EuropeanOption::operator=(const EuropeanOption &option2)
{
    if (this==&option2) return *this;
    copy(option2);
    return *this;
}

double EuropeanOption::Price() const
{
    if (optType_ == "C")
    {
        return callPrice();
    }
    else
    {
        return putPrice();
    }
}

double EuropeanOption::Delta() const
{
    if (optType_ == "C")
    {
        return callDeltat();
    }
    else
    {
        return putDeltat();
    }
}

void EuropeanOption::toggle()
{ // Change option type (C/P, P/C)
    if (optType_ == "C")
        optType_ = "P";
    else 
        optType_ = "C";
}
