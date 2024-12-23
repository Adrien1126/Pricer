#ifndef GRID_H
#define GRID_H

#include <vector>
#include <functional>

class Grid {
private:
    std::vector<double> values; // Contient les points de la grille
    double start;               // Début de la grille
    double end;                 // Fin de la grille
    int numPoints;              // Nombre de points dans la grille

public:
    // Constructeur pour une grille uniforme
    Grid(double start, double end, int numPoints);

    // Méthode pour obtenir les points de la grille
    const std::vector<double>& getValues() const;

    // Méthode statique pour générer une grille uniforme
    static Grid createUniformGrid(double start, double end, int numPoints);

    // Méthode statique pour générer une grille logarithmique
    static Grid createLogarithmicGrid(double start, double end, int numPoints);

    // Méthode pour afficher la grille (utile pour le débogage)
    void print() const;
};

#endif // GRID_H
