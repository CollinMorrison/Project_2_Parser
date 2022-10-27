//
// Created by Collin Morrison on 10/27/22.
//

#include "Tuple.h"


bool Tuple::operator<(const Tuple &rhs) const {
    return this->values < rhs.values;
}