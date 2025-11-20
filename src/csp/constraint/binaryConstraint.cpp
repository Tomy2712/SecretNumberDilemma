//
// Created by Tom on 17/11/2025.
//

#include "secretNumberDilemma/csp/constraint/binaryConstraint.h"

namespace secretNumberDilemma {
    BinaryConstraint::BinaryConstraint(Variable *variable1, Variable *variable2, const uchar res): var1(variable1), var2(variable2), res(res) {}

} // secretNumberDilemma