#ifndef EuropeanOption_HPP
#define EuropeanOption_HPP
#include <string>
using namespace std;

class EuropeanOption {
private:
    
    void init(); // initialize all default values
    void copy(const EuropeanOption& o2); // copy
    // "Kernel" functions for option calculations 
    double callPrice() const;
    double putPrice() const;
    double callDeltat() const;
    double putDeltat() const;

public:
    // Public member data for convenience only
    double S_;  // initial stock price
    double K_;  // strike price
    double T_;  // time to expiration in years
    double r_;  // risk-free interest rate
    double sigma_;  // volatility of the stock
    double b_; //cost of carry (b=0 for a future option)
    string optType_; // Option name (call, put)

public:
// Constructors 
    EuropeanOption(); // Default call option
    EuropeanOption(const EuropeanOption& option2); // copy constructor
    EuropeanOption(const string& optionType); // Create option type

    // Destructor
    virtual ~EuropeanOption();

    // Assignment operator
    EuropeanOption& operator=(const EuropeanOption& option2);

    // Function that calculates option price and (some) sensitivities
    double Price() const;
    double Delta() const;

    // Modifier functions 
    void toggle();  // Change option type (C/P, P/C)
};  

double N(double x);

#endif  // EuropeanOption_HPP