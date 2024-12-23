#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "../include/Rate.h"
#include "../include/EuropeanOption.h"
#include "../include/Grid.h"
#include "../include/CranckNicolson.h"

// Fonction pour exporter les résultats dans un fichier CSV
void exportResultsToCSV(const std::vector<std::vector<double>>& priceGrid,
                        const Grid& spotGrid, const Grid& timeGrid,
                        const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier pour exporter les résultats.");
    }

    const std::vector<double>& spotValues = spotGrid.getValues();
    const std::vector<double>& timeValues = timeGrid.getValues();

    // En-tête
    file << "Spot\\Time,";
    for (double t : timeValues) {
        file << t << ",";
    }
    file << "\n";

    // Données
    for (size_t i = 0; i < spotValues.size(); ++i) {
        file << spotValues[i] << ",";
        for (size_t j = 0; j < timeValues.size(); ++j) {
            file << priceGrid[j][i] << ",";
        }
        file << "\n";
    }

    file.close();
}

// Fonction pour tester le schéma Cranck-Nicolson
void testCranckNicolson() {
    // Déclaration d'un vecteur de taux (dépendance au temps)
    std::vector<std::tuple<double, double>> rateData = {
        {0.0, 0.05}, {0.5, 0.045}, {1.0, 0.04}, {2.0, 0.03}
    };
    Rate rateInterpolator(rateData);

    // Définir les paramètres de l'option
    double spot = 80.0;
    double strike = 100.0;
    double maturity = 1.0;
    double volatility = 0.2;
    bool isCall = true;

    // Récupération du taux interpolé
    double rate = rateInterpolator.getRate(maturity);

    EuropeanOption option(spot, strike, maturity, rate, volatility, isCall);

    // Paramètres de discrétisation
    double spotMax = 300.0;
    int numSpotSteps = 2001;
    int numTimeSteps = 2000;
    Grid spotGrid = Grid::createUniformGrid(0.0, spotMax, numSpotSteps);
    Grid timeGrid = Grid::createUniformGrid(0.0, maturity, numTimeSteps);

    // Calcul des prix avec Cranck-Nicolson
    std::vector<std::vector<double>> priceGrid = CranckNicolson::priceEuropeanGrid(option, spotGrid, timeGrid);

    // Exporter les résultats
    exportResultsToCSV(priceGrid, spotGrid, timeGrid, "cranck_nicolson_results.csv");

    // Vérification avec Black-Scholes à t = 0
    const std::vector<double>& spotValues = spotGrid.getValues();
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Spot\tCranck-Nicolson\tBlack-Scholes\tEcart (%)\n";
    for (size_t i = 0; i < spotValues.size(); ++i) {
        double spotTest = spotValues[i];
        EuropeanOption testOption(spotTest, strike, maturity, rateInterpolator.getRate(maturity), volatility, isCall);
        double bsPrice = testOption.calculateBSPrice(); // Prix Black-Scholes
        double cnPrice = priceGrid[0][i];               // Prix Cranck-Nicolson à t = 0

        // Calcul de l'écart en pourcentage
        double percentageError = (bsPrice != 0.0) ? std::abs(cnPrice - bsPrice) / bsPrice * 100.0 : 0.0;

        // Affichage des résultats
        std::cout << spotTest << "\t" << cnPrice << "\t" << bsPrice << "\t" << percentageError << "%\n";
    }
}

int main() {
    try {
        testCranckNicolson();
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }
    return 0;
}
