#include "../include/Utilities.h"

// Fonction de répartition cumulée de la loi normale
double norm_cdf(double x) {
    return 0.5 * (1.0 + std::erf(x / std::sqrt(2.0)));
}
