//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINTTESTER_H
#define SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINTTESTER_H

#include "tester.h"
#include "secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

namespace secretNumberDilemma {

    class AllDifferenceConstraintTester final : public Tester {
    public:
        AllDifferenceConstraintTester() = default;
        ~AllDifferenceConstraintTester() override = default;

        static void runTests();

    private:
        static void testNoModification();
        static void testSingleRemoval();
    };

} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_ALLDIFFERENCECONSTRAINTTESTER_H