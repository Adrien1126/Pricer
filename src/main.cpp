#include <iostream>
#include <vector>
#include <tuple>
#include <iomanip>
#include <algorithm>
#include "../include/Rate.h"
#include "../include/EuropeanOption.h"
#include "../include/Grid.h"
#include "../include/CranckNicolson.h"

void verifyBoundaryConditions(const std::vector<std::vector<double>>& priceGrid,
                              const Grid& spotGrid, const Grid& timeGrid,
                              const EuropeanOption& option) {
    const std::vector<double>& spotValues = spotGrid.getValues();
    const std::vector<double>& timeValues = timeGrid.getValues();
    double strike = option.getStrike();
    double rate = option.getRate();
    bool isCall = option.getIsCall();

    // Vérifier la condition aux limites à S = 0
    if (isCall) {
        for (size_t t = 0; t < timeValues.size(); ++t) {
            if (std::abs(priceGrid[t][0]) > 1e-6) {
                std::cerr << "Condition aux limites incorrecte à S=0 pour t=" << timeValues[t] << ": V(0, t) = " << priceGrid[t][0] << "\n";
            }
        }
    } else { // Put option
        for (size_t t = 0; t < timeValues.size(); ++t) {
            if (std::abs(priceGrid[t][0] - strike * exp(-rate * timeValues[t])) > 1e-6) {
                std::cerr << "Condition aux limites incorrecte à S=0 pour t=" << timeValues[t]
                          << ": V(0, t) = " << priceGrid[t][0] << ", attendu = " << strike * exp(-rate * timeValues[t]) << "\n";
            }
        }
    }

    // Vérifier la condition aux limites à S → infini (approximé avec spotMax)
    double spotMax = spotValues.back();
    for (size_t t = 0; t < timeValues.size(); ++t) {
        double expectedLimit = (isCall)
                                   ? spotMax - strike * exp(-rate * timeValues[t])
                                   : strike * exp(-rate * timeValues[t]) - spotMax;
        if (std::abs(priceGrid[t].back() - expectedLimit) > 1e-6) {
            std::cerr << "Condition aux limites incorrecte à S=spotMax pour t=" << timeValues[t]
                      << ": V(S_max, t) = " << priceGrid[t].back() << ", attendu = " << expectedLimit << "\n";
        }
    }
}

void testCases(const std::vector<std::tuple<double, double, double>>& testParams,
               const Rate& rateInterpolator, const Grid& spotGrid, const Grid& timeGrid) {
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Strike\tMaturity\tVolatility\tTaux (r)\tSpot (S)\tBS Price\tCN Price\tEcart (%)\n";

    for (const auto& [strike, maturity, volatility] : testParams) {
        try {
            double spot = 80.0; // Spot initial
            bool isCall = true; // Option call
            double rate = rateInterpolator.getRate(maturity);

            // Créer une option avec ces paramètres
            EuropeanOption option(spot, strike, maturity, rate, volatility, isCall);

            // Calcul des prix avec Cranck-Nicolson
            std::vector<std::vector<double>> priceGrid = CranckNicolson::priceEuropeanGrid(option, spotGrid, timeGrid);

            // Vérification des conditions aux limites
            verifyBoundaryConditions(priceGrid, spotGrid, timeGrid, option);

            // Recherche et interpolation pour le spot initial
            const std::vector<double>& spotValues = spotGrid.getValues();
            double cnPrice = 0.0;
            auto upper = std::upper_bound(spotValues.begin(), spotValues.end(), spot);
            if (upper == spotValues.end() || upper == spotValues.begin()) {
                throw std::runtime_error("Spot hors des limites de la grille.");
            }
            size_t idx1 = std::distance(spotValues.begin(), upper) - 1;
            size_t idx2 = idx1 + 1;

            // Interpolation linéaire
            double S1 = spotValues[idx1];
            double S2 = spotValues[idx2];
            double P1 = priceGrid[0][idx1];
            double P2 = priceGrid[0][idx2];
            cnPrice = P1 + (P2 - P1) * (spot - S1) / (S2 - S1);

            // Calcul du prix analytique avec Black-Scholes
            double bsPrice = option.calculateBSPrice();

            // Calcul de l'écart en pourcentage
            double percentageError = (bsPrice != 0.0) ? std::abs(cnPrice - bsPrice) / bsPrice * 100.0 : 0.0;

            // Affichage des résultats
            std::cout << strike << "\t" << maturity << "\t\t" << volatility << "\t\t" << rate << "\t\t"
                      << spot << "\t\t" << bsPrice << "\t" << cnPrice << "\t" << percentageError << "%\n";

        } catch (const std::exception& e) {
            std::cerr << "Erreur : " << e.what() << std::endl;
        }
    }
}

int main() {
    try {
        // Déclaration d'un vecteur de taux
        std::vector<std::tuple<double, double>> rateData = {
            {0.0, 0.05}, {0.5, 0.045}, {1.0, 0.04}, {2.0, 0.03} // Exemple de courbe des taux
        };
        Rate rateInterpolator(rateData);

        // Paramètres de discrétisation
        double spotMax = 300.0;
        int numSpotSteps = 2001;
        int numTimeSteps = 2000;
        Grid spotGrid = Grid::createUniformGrid(0.0, spotMax, numSpotSteps);
        Grid timeGrid = Grid::createUniformGrid(0.0, 2.0, numTimeSteps); // Max maturity = 2.0

        // Liste des paramètres à tester (strike, maturité, volatilité)
        std::vector<std::tuple<double, double, double>> testParams = {
            {100.0, 1.0, 0.2},  // Cas standard
            {120.0, 1.0, 0.2},  // Strike plus élevé
            {80.0, 1.0, 0.2},   // Strike plus faible
            {100.0, 0.5, 0.2},  // Maturité plus courte
            {100.0, 2.0, 0.2},  // Maturité plus longue
            {100.0, 1.0, 0.1},  // Volatilité plus faible
            {100.0, 1.0, 0.3}   // Volatilité plus élevée
        };

        // Tester différents cas
        testCases(testParams, rateInterpolator, spotGrid, timeGrid);

    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
