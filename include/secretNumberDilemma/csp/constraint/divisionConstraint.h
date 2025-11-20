//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_DIVISIONCONSTRATINT_H
#define SECRETNUMBERDILEMMA_DIVISIONCONSTRATINT_H

#include <algorithm>

#include "binaryConstraint.h"

namespace secretNumberDilemma {
    class DivisionConstraint final : public BinaryConstraint {
    public:
        DivisionConstraint(Variable* var1, Variable* var2, uchar res);

        bool filterDomain() override;
        bool simulateConstraint(State &state) override;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_DIVISIONCONSTRATINT_H