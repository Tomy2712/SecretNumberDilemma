//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ADDITIVECONSTRAINT_H
#define SECRETNUMBERDILEMMA_ADDITIVECONSTRAINT_H

#include "binaryConstraint.h"

namespace secretNumberDilemma {
    class AdditiveConstraint final : public BinaryConstraint {
    public:
        AdditiveConstraint(Variable *v1, Variable *v2, uchar res);
        ~AdditiveConstraint() override = default;


        bool filterDomain() override;


        bool simulateConstraint(State &state) override;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_ADDITIVECONSTRAINT_H