//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINTTESTER_H
#define SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINTTESTER_H


#include "tester.h"
#include "secretNumberDilemma/csp/constraint/multiplicativeConstraint.h"

namespace secretNumberDilemma {
    class MultiplicativeConstraintTester final : public Tester {
    public:
        static void runTests();
    private:
        static void testSingleRemoval();

    };
}

#endif //SECRETNUMBERDILEMMA_MULTIPLICATIVECONSTRAINTTESTER_H