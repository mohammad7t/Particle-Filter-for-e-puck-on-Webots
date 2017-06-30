//
// Created by mohamad on 6/28/2017.
//

#ifndef MYCONTROLLER_ACTION_H
#define MYCONTROLLER_ACTION_H

#include "common.h"

class Action{
public:

    double rotateRadian;
    double distance;
};

ostream &operator<<(ostream &out, const Action &a);
#endif //MYCONTROLLER_ACTION_H
