#include "common.h"
#include <cstdlib>

double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

double randMToN(double M, double N) {
    return M + (rand() / (RAND_MAX / (N - M)));
}
