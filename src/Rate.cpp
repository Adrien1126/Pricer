#include "../include/Rate.h"

Rate::Rate(const std::vector<std::tuple<double, double>> &rateData) : rates(rateData) {
    // Tri des données par ordre croissant des t_k
    std::sort(rates.begin(), rates.end(), [](const auto &a, const auto &b) {
        return std::get<0>(a) < std::get<0>(b);
    });
}

double Rate::getRate(double t) const {
    if (rates.empty()) {
        throw std::runtime_error("Le vecteur des taux est vide.");
    }

    // Si t est hors des bornes, renvoyer les extrêmes
    if (t <= std::get<0>(rates.front())) {
        return std::get<1>(rates.front());
    }
    if (t >= std::get<0>(rates.back())) {
        return std::get<1>(rates.back());
    }

    // Recherche de l'intervalle [t_k, t_k+1]
    for (size_t i = 0; i < rates.size() - 1; ++i) {
        double t_k = std::get<0>(rates[i]);
        double t_k1 = std::get<0>(rates[i + 1]);
        double r_k = std::get<1>(rates[i]);
        double r_k1 = std::get<1>(rates[i + 1]);

        if (t_k <= t && t <= t_k1) {
            // Interpolation linéaire
            return r_k + (r_k1 - r_k) * (t - t_k) / (t_k1 - t_k);
        }
    }

    // Cela ne devrait jamais arriver
    throw std::runtime_error("Erreur d'interpolation.");
}