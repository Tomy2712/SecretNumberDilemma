//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_CONSTRAINT_H
#define SECRETNUMBERDILEMMA_CONSTRAINT_H


#include "secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/utils/utils.h"

namespace secretNumberDilemma {

    class Constraint {
    public:
        virtual ~Constraint() = default;


        virtual bool filterDomain() = 0;

        virtual bool simulateConstraint(State &state) = 0;
    private:

    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_CONSTRAINT_H