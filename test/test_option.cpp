#include <iostream>
#include <cassert>
#include "../include/EuropeanOption.h"

void testEuropeanCallOption() {
    EuropeanOption callOption(100, 105, 1.0, 0.05, 0.2, true);
    double price = callOption.calculateBSPrice();

    assert(price > 0.0 && "Le prix d'un call doit être positif.");
    std::cout << "Test call européen : OK (" << price << ")" << std::endl;
}

void testEuropeanPutOption() {
    EuropeanOption putOption(100, 95, 1.0, 0.05, 0.2, false);
    double price = putOption.calculateBSPrice();

    assert(price > 0.0 && "Le prix d'un put doit être positif.");
    std::cout << "Test put européen : OK (" << price << ")" << std::endl;
}

int main() {
    testEuropeanCallOption();
    testEuropeanPutOption();

    std::cout << "Tous les tests sur les options sont passés avec succès !" << std::endl;
    return 0;
}
