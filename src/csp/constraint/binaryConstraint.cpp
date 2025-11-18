//
// Created by Tom on 17/11/2025.
//

#include "secretNumberDilemma/csp/constraint/binaryConstraint.h"

namespace secretNumberDilemma {
    BinaryConstraint::BinaryConstraint(Variable *variable1, Variable *variable2, unsigned char res): variable1(variable1), variable2(variable2), res(res) {}

} // secretNumberDilemma