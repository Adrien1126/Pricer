#ifndef CRANKNICOLSON_H
#define CRANKNICOLSON_H

#include <vector>
#include "Option.h"
#include "Grid.h"

class CranckNicolson {
public:
    // Calcul du prix d'une option européenne avec Cranck-Nicolson
    static std::vector<double> priceEuropean(
        const Option& option, const Grid& spotGrid, const Grid& timeGrid);
    
    // Méthode pour calculer la grille complète des prix
    static std::vector<std::vector<double>> priceEuropeanGrid(const Option& option, const Grid& spotGrid, const Grid& timeGrid);

private:
    // Méthode pour résoudre un système tridiagonal (algorithme de Thomas)
    static std::vector<double> solveTridiagonal(const std::vector<double>& a,
                                                const std::vector<double>& b,
                                                const std::vector<double>& c,
                                                const std::vector<double>& d);

    

};

#endif // CRANKNICOLSON_H
