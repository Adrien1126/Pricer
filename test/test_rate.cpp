#include <iostream>
#include <cassert>
#include "../include/Rate.h"

void testRateEmptyData() {
    try {
        Rate rate({});
        rate.getRate(1.0);
        assert(false && "Un vecteur vide devrait lever une exception.");
    } catch (const std::runtime_error &e) {
        std::cout << "Test vide : OK (" << e.what() << ")" << std::endl;
    }
}

void testRateOutOfBounds() {
    std::vector<std::tuple<double, double>> rateData = {
        {0.0, 0.01}, {1.0, 0.02}, {2.0, 0.025}};
    Rate rate(rateData);

    assert(rate.getRate(-1.0) == 0.01 && "Le taux hors bornes inférieures devrait être égal au premier taux.");
    assert(rate.getRate(3.0) == 0.025 && "Le taux hors bornes supérieures devrait être égal au dernier taux.");
    std::cout << "Test hors bornes : OK" << std::endl;
}

void testRateInterpolation() {
    std::vector<std::tuple<double, double>> rateData = {
        {0.0, 0.01}, {1.0, 0.02}, {2.0, 0.025}};
    Rate rate(rateData);

    double interpolated = rate.getRate(1.5);
    assert(interpolated == 0.0225 && "L'interpolation pour t=1.5 devrait donner 0.0225.");

    interpolated = rate.getRate(0.5);
    assert(interpolated == 0.015 && "L'interpolation pour t=0.5 devrait donner 0.015.");

    std::cout << "Test interpolation : OK" << std::endl;
}

int main() {
    testRateEmptyData();
    testRateOutOfBounds();
    testRateInterpolation();

    std::cout << "Tous les tests sont passés avec succès !" << std::endl;
    return 0;
}
