#include "../ReusableCode/EuropeanOption.hpp"
#include <iostream>

int main()
{
    // Call option on a stock
    EuropeanOption callOption;
    cout << "Call option on a stock: " << callOption.Price() << endl;
    // Put option on a stock index
    EuropeanOption indexOption;
    indexOption.optType_ = "P";
    indexOption.S_ = 100.0;
    indexOption.K_ = 95.0;
    indexOption.T_ = 0.5;
    indexOption.r_ = 0.10;
    indexOption.sigma_ = 0.20;
    double q = 0.05; // Dividend yield 
    indexOption.b_ = indexOption.r_ - q;

    cout << "Put option on index: " << indexOption.Price() << endl;
    // Call and put options on a future
    EuropeanOption futureOption;
    futureOption.optType_ = "P";
    futureOption.S_ = 19.0;
    futureOption.K_ = 19.0;
    futureOption.T_ = 0.75;
    futureOption.r_ = 0.10;
    futureOption.sigma_ = 0.28;
    futureOption.b_ = 0.0;

    cout << "Put option on future: " << futureOption.Price() << endl;

    // Now change over to a call on the option
    futureOption.toggle();
    cout << "Call on future: " << futureOption.Price() << endl;
    return 0;
}
