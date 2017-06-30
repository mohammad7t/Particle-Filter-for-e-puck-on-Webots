#include "common.h"
#include <cstdlib>

double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

double randMToN(double M, double N) {
    N -= 1e-9;
    return M + (rand() / (RAND_MAX / (N - M)));
}
