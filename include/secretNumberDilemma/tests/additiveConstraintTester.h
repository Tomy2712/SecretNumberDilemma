//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ADDITIVECONSTRAINTTESTER_H
#define SECRETNUMBERDILEMMA_ADDITIVECONSTRAINTTESTER_H

#include "tester.h"
#include "secretNumberDilemma/csp/constraint/additiveConstraint.h"

namespace secretNumberDilemma {
    class AdditiveConstraintTester final: public Tester {
    public:
        static void runTests();

    private:
        static void testSingleRemoval();
    };

}


#endif //SECRETNUMBERDILEMMA_ADDITIVECONSTRAINTTESTER_H