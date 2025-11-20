//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ZEROCONSTRAINTTESTER_H
#define SECRETNUMBERDILEMMA_ZEROCONSTRAINTTESTER_H

#include "secretNumberDilemma/csp/constraint/zeroConstraint.h"
#include "tester.h"

namespace secretNumberDilemma {
    class ZeroConstraintTester final : public Tester {
    public:
        static void runTests();

    private:
        static void testSingleRemoval();
    };
    ;
}




#endif //SECRETNUMBERDILEMMA_ZEROCONSTRAINTTESTER_H