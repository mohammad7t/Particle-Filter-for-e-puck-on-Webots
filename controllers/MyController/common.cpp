#include "common.h"
#include <cstdlib>

double randZeroToOne() {
    return rand() / (RAND_MAX + 1.);
}

double randMToN(double M, double N) {
    return M + (rand() / (RAND_MAX / (N - M)));
}

std::ostream &operator<<(std::ostream &out, const vector<double> &rhs) {
    out << '{';
    for (int i = 0; i < rhs.size(); i++) {
        out << rhs[i];
        if (i + 1 < rhs.size()) {
            out << ',';
        }
    }
    out << '}';
    return out;
}