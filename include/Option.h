#ifndef OPTION_H
#define OPTION_H

#include <string>

class Option {
protected:
    double spot;       // Prix initial du sous-jacent (S0)
    double strike;     // Prix d'exercice (K)
    double maturity;   // Temps à maturité (T)
    double rate;       // Taux sans risque (r)
    double volatility; // Volatilité (σ)
    bool isCall;       // true pour call, false pour put

public:
    // Constructeur
    Option(double spot, double strike, double maturity, double rate, double volatility, bool isCall);

    // Accesseurs
    double getSpot() const;
    double getStrike() const;
    double getMaturity() const;
    double getRate() const;
    double getVolatility() const;
    bool getIsCall() const;

    // Méthode virtuelle pour calculer le prix
    virtual double calculateBSPrice() const = 0; // Méthode pure virtuelle

    // Destructeur virtuel
    virtual ~Option() = default;
};

#endif // OPTION_H
