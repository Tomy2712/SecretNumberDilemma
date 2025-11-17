//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H
#define SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H

#include "constraint.h"
#include "../variable.h"

namespace secretNumberDilemma {
    class BinaryConstraint: public Constraint {
    public:
        BinaryConstraint(Variable *variable1, Variable *variable2);
        ~BinaryConstraint() override = 0;

    protected:
        Variable *variable1;
        Variable *variable2;

    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_BINARY_CONSTRAINT_H