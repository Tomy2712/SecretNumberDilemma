//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H
#define SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H

#include <vector>

#include "binaryConstraint.h"

namespace secretNumberDilemma {
    class AllDifferenceConstraint final : public Constraint {
    public:
        explicit AllDifferenceConstraint(const std::vector<Variable *> &variables);

        bool filterDomain() override;
    private:
        std::vector<Variable *> variables;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H