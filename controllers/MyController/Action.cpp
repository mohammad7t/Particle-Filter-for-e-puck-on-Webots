//
// Created by mohammad on 6/30/2017.
//

#include "Action.h"

ostream &operator<<(ostream &out, const Action &a) {
    out << "A[" << a.distance << ',' << a.rotateRadian << ']';
    return out;
}
