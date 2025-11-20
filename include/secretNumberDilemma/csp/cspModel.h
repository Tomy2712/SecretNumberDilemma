//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_CSPMODEL_H
#define SECRETNUMBERDILEMMA_CSPMODEL_H

#include <vector>
#include <memory>

#include "secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/csp/constraint/constraint.h"
#include "secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

namespace secretNumberDilemma {
    class CspModel {
    public:
        explicit CspModel(std::vector<std::shared_ptr<Variable>> &variables);

        ~CspModel() = default;

        void applyConstraints() const;

        void addConstraint(std::unique_ptr<Constraint> constraint);

        std::vector<std::vector<uchar>> simulateConstraint(Constraint *constraint);

    private:
        std::vector<std::shared_ptr<Variable>> &variables;
        std::vector<std::unique_ptr<Constraint>> constraints;
    };
}



#endif //SECRETNUMBERDILEMMA_CSPMODEL_H