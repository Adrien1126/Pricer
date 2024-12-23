#ifndef __Rate_H__
#define __Rate_H__
#include <vector>
class Rate
{
private:
    // Stocke les paires (t_k, r(t_k))
    std::vector<std::tuple<double, double>> rates;
public:
    // Constructeur : prend un vecteur de tuples (t_k, r(t_k))
    Rate(const std::vector<std::tuple<double, double>>& rateData); 
    // Renvoie le taux d'intérêt à la date t par interpolation linéaire 
    // La date t est un double et correspond à la durée en années entre la date de calcul et la maturité pour une option européenne 
    double getRate(double t) const;
};

#endif // __Rate_H__