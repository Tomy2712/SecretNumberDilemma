//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H
#define SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H

#include <vector>

#include "constraint.h"
#include "../variable.h"

namespace secretNumberDilemma {
    class BinaryConstraint: public Constraint {
    public:
        BinaryConstraint(Variable *variable1, Variable *variable2, uchar res);
        ~BinaryConstraint() override = default;

    protected:
        Variable *var1;
        Variable *var2;

        uchar res;

    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H