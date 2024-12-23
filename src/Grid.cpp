#include "../include/Grid.h"
#include <iostream>

// Constructeur pour une grille uniforme
Grid::Grid(double start, double end, int numPoints)
    : start(start), end(end), numPoints(numPoints) {
    if (numPoints < 2) {
        throw std::invalid_argument("Le nombre de points doit être supérieur ou égal à 2.");
    }
    double step = (end - start) / (numPoints - 1);
    for (int i = 0; i < numPoints; ++i) {
        values.push_back(start + i * step);
    }
}

// Retourne les points de la grille
const std::vector<double>& Grid::getValues() const {
    return values;
}

// Méthode statique pour créer une grille uniforme
Grid Grid::createUniformGrid(double start, double end, int numPoints) {
    return Grid(start, end, numPoints);
}

// Méthode pour afficher les points de la grille
void Grid::print() const {
    for (const auto& value : values) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

Grid Grid::createLogarithmicGrid(double start, double end, int numPoints) {
    if (start <= 0.0 || end <= 0.0) {
        throw std::invalid_argument("Les bornes doivent être positives pour une grille logarithmique.");
    }
    Grid grid(start, end, numPoints);
    grid.values.clear(); // Effacer les valeurs actuelles
    double logStart = std::log(start);
    double logEnd = std::log(end);
    double step = (logEnd - logStart) / (numPoints - 1);
    for (int i = 0; i < numPoints; ++i) {
        grid.values.push_back(std::exp(logStart + i * step));
    }
    return grid;
}
