#include <iostream>
#include <cassert>
#include "../include/Grid.h"

// Test pour une grille uniforme
void testUniformGrid() {
    double start = 0.0, end = 200.0;
    int numPoints = 21;

    // Créer la grille uniforme
    Grid uniformGrid = Grid::createUniformGrid(start, end, numPoints);

    // Récupérer les valeurs
    const std::vector<double>& values = uniformGrid.getValues();

    // Vérifier le nombre de points
    assert(values.size() == static_cast<size_t>(numPoints) && "Le nombre de points est incorrect.");

    // Vérifier les bornes
    assert(values.front() == start && "La borne inférieure de la grille est incorrecte.");
    assert(values.back() == end && "La borne supérieure de la grille est incorrecte.");

    // Vérifier l'uniformité
    double expectedStep = (end - start) / (numPoints - 1);
    for (size_t i = 1; i < values.size(); ++i) {
        assert(std::abs(values[i] - values[i - 1] - expectedStep) < 1e-6 &&
               "La grille n'est pas uniforme.");
    }

    std::cout << "Test de la grille uniforme : OK" << std::endl;
}

// Test pour une erreur sur un nombre de points invalide
void testInvalidGrid() {
    try {
        Grid invalidGrid = Grid::createUniformGrid(0.0, 200.0, 1);
        assert(false && "Une exception aurait dû être levée pour un nombre de points < 2.");
    } catch (const std::invalid_argument& e) {
        std::cout << "Test des paramètres invalides : OK (" << e.what() << ")" << std::endl;
    }
}

int main() {
    // Lancer les tests
    testUniformGrid();
    testInvalidGrid();

    std::cout << "Tous les tests pour Grid sont passés avec succès !" << std::endl;
    return 0;
}
