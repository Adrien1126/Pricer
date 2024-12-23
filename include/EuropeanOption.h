#ifndef EUROPEANOPTION_H
#define EUROPEANOPTION_H

#include "Option.h"

class EuropeanOption : public Option {
public:
    // Constructeur
    EuropeanOption(double spot, double strike, double maturity, double rate, double volatility, bool isCall);

    // Implémentation de la méthode de calcul du prix avec la formule explicite de Black-Scholes
    double calculateBSPrice() const override;
};

#endif // EUROPEANOPTION_H
