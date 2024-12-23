#include "../include/CranckNicolson.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

// Méthode pour résoudre un système tridiagonal
std::vector<double> CranckNicolson::solveTridiagonal(const std::vector<double>& a,
                                                    const std::vector<double>& b,
                                                    const std::vector<double>& c,
                                                    const std::vector<double>& d) {
    int n = b.size();
    std::vector<double> x(n), cp(n), dp(n);

    // Forward sweep
    cp[0] = c[0] / b[0];
    dp[0] = d[0] / b[0];
    for (int i = 1; i < n; ++i) {
        double denom = b[i] - a[i] * cp[i - 1];
        cp[i] = c[i] / denom;
        dp[i] = (d[i] - a[i] * dp[i - 1]) / denom;
    }

    // Backward substitution
    x[n - 1] = dp[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = dp[i] - cp[i] * x[i + 1];
    }

    return x;
}

std::vector<std::vector<double>> CranckNicolson::priceEuropeanGrid(const Option& option, const Grid& spotGrid, const Grid& timeGrid) {
    
    const std::vector<double>& S = spotGrid.getValues();
    const std::vector<double>& T = timeGrid.getValues();
    int N_S = S.size();
    int N_T = T.size();

    double dS = S[1] - S[0];
    double dt = T[1] - T[0];

    // Initialisation de la grille des prix
    std::vector<std::vector<double>> priceGrid(N_T, std::vector<double>(N_S, 0.0));

    // Initialisation des conditions aux limites à maturité (t = T)
    for (int i = 0; i < N_S; ++i) {
        priceGrid[N_T - 1][i] = std::max(option.getIsCall() ? (S[i] - option.getStrike()) : (option.getStrike() - S[i]), 0.0);
    }

    // Boucle pour résoudre le problème à chaque pas de temps
    std::vector<double> V(N_S); // Valeurs pour un instant t
    std::vector<double> V_new(N_S);

    for (int t = N_T - 2; t >= 0; --t) {
        // Charger les valeurs actuelles de la grille
        for (int i = 0; i < N_S; ++i) {
            V[i] = priceGrid[t + 1][i];
        }

        // Construction des matrices tridiagonales
        std::vector<double> a(N_S - 2), b(N_S - 2), c(N_S - 2), d(N_S - 2);
        for (int i = 1; i < N_S - 1; ++i) {
            double sigma2 = 0.5 * option.getVolatility() * option.getVolatility();
            double r = option.getRate();

            a[i - 1] = -0.25 * dt * (sigma2 * i * i - r * i);
            b[i - 1] = 1.0 + 0.5 * dt * (sigma2 * i * i + r);
            c[i - 1] = -0.25 * dt * (sigma2 * i * i + r * i);
            d[i - 1] = (1.0 - 0.5 * dt * (sigma2 * i * i + r)) * V[i] +
                       0.25 * dt * (sigma2 * i * i - r * i) * V[i - 1] +
                       0.25 * dt * (sigma2 * i * i + r * i) * V[i + 1];
        }

        // Résolution du système tridiagonal
        std::vector<double> V_internal = solveTridiagonal(a, b, c, d);

        // Mise à jour des valeurs
        for (int i = 1; i < N_S - 1; ++i) {
            V_new[i] = V_internal[i - 1];
        }

        V_new[0] = 0.0;          // Condition limite pour S_min
        V_new[N_S - 1] = S[N_S - 1] - option.getStrike() * exp(-option.getRate() * T[t]); // Asymptotique pour S_max

        // Stocker les valeurs dans la grille
        for (int i = 0; i < N_S; ++i) {
            priceGrid[t][i] = V_new[i];
        }
    }

    return priceGrid;
}


// Calcul du prix d'une option européenne
std::vector<double> CranckNicolson::priceEuropean(
    const Option& option, const Grid& spotGrid, const Grid& timeGrid) {
    
    const std::vector<double>& S = spotGrid.getValues();
    const std::vector<double>& T = timeGrid.getValues();
    int N_S = S.size();
    int N_T = T.size();

    double dS = S[1] - S[0];
    double dt = T[1] - T[0];

    std::vector<double> V(N_S); // Valeurs à maturité
    std::vector<double> V_new(N_S);

    // Initialisation des conditions aux limites
    for (int i = 0; i < N_S; ++i) {
        V[i] = std::max(option.getIsCall() ? (S[i] - option.getStrike()) : (option.getStrike() - S[i]), 0.0);
    }

    // Boucle sur les pas de temps
    for (int t = N_T - 2; t >= 0; --t) {
        // Construction des matrices tridiagonales
        std::vector<double> a(N_S - 2), b(N_S - 2), c(N_S - 2), d(N_S - 2);
        for (int i = 1; i < N_S - 1; ++i) {
            double sigma2 = 0.5 * option.getVolatility() * option.getVolatility();
            double r = option.getRate();

            a[i - 1] = -0.25 * dt * (sigma2 * i * i - r * i);
            b[i - 1] = 1.0 + 0.5 * dt * (sigma2 * i * i + r);
            c[i - 1] = -0.25 * dt * (sigma2 * i * i + r * i);
            d[i - 1] = (1.0 - 0.5 * dt * (sigma2 * i * i + r)) * V[i] +
                       0.25 * dt * (sigma2 * i * i - r * i) * V[i - 1] +
                       0.25 * dt * (sigma2 * i * i + r * i) * V[i + 1];
        }

        // Résolution du système tridiagonal
        std::vector<double> V_internal = solveTridiagonal(a, b, c, d);

        // Mise à jour des valeurs
        for (int i = 1; i < N_S - 1; ++i) {
            V_new[i] = V_internal[i - 1];
        }

        // Obtenir le taux sans risque à l'instant t
        double rate_at_t = option.getRate();

        // Condition aux limites pour S_min
        V_new[0] = 0.0; // Condition limite pour S_min

        // Condition aux limites pour S_max
        // Mettre à jour la condition en fonction du taux interpolé à chaque instant t
        V_new[N_S - 1] = S[N_S - 1] - option.getStrike() * exp(-rate_at_t * T[t]);

        V = V_new; // Mise à jour pour le prochain pas de temps
    }

    return V;
}
