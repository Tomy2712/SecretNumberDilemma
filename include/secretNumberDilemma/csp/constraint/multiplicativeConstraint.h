//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINT_H
#define SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINT_H

#include "binaryConstraint.h"


namespace secretNumberDilemma {
    class MultiplicativeConstraint final : public BinaryConstraint {
    public:
        MultiplicativeConstraint(Variable* var1, Variable* var2, uchar res);

        bool filterDomain() override;
        bool simulateConstraint(State &state) override;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINT_H