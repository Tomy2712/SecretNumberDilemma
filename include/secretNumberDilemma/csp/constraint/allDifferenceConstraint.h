//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H
#define SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H

#include <vector>
#include <memory>

#include "binaryConstraint.h"

namespace secretNumberDilemma {
    class AllDifferenceConstraint final : public Constraint {
    public:
        explicit AllDifferenceConstraint(const std::vector<std::shared_ptr<Variable>> &variables);


        bool filterDomain() override;
        bool simulateConstraint(State &state) override;
    private:
        std::vector<std::shared_ptr<Variable>> variables;



    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINT_H