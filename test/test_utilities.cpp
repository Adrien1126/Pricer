#include <iostream>
#include <cassert>
#include "../include/Utilities.h"

void testNormCdf() {
    double x1 = 0.0;
    double x2 = 1.0;
    double x3 = -1.0;

    // Vérification de quelques valeurs attendues
    assert(std::abs(norm_cdf(x1) - 0.5) < 1e-6 && "Erreur : N(0) devrait être 0.5.");
    assert(std::abs(norm_cdf(x2) - 0.841344746) < 1e-6 && "Erreur : N(1) devrait être ~0.8413.");
    assert(std::abs(norm_cdf(x3) - 0.158655254) < 1e-6 && "Erreur : N(-1) devrait être ~0.1587.");

    std::cout << "Tous les tests sur norm_cdf sont passés avec succès !" << std::endl;
}

int main() {
    testNormCdf();
    return 0;
}
