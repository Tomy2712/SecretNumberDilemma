//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_DIVISIONCONSTRAINTTESTER_H
#define SECRETNUMBERDILEMMA_DIVISIONCONSTRAINTTESTER_H


#include "tester.h"
#include "secretNumberDilemma/csp/constraint/divisionConstraint.h"

namespace secretNumberDilemma {
    class DivisionConstraintTester final : public Tester {
    public:
        static void runTests();
    private:
        static void testSingleRemoval();

    };
}

#endif //SECRETNUMBERDILEMMA_DIVISIONCONSTRAINTTESTER_H