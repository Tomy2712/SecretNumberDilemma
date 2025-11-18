//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_VARIABLETESTER_H
#define SECRETNUMBERDILEMMA_VARIABLETESTER_H

#include "tester.h"
#include "secretNumberDilemma/csp/variable.h"

namespace secretNumberDilemma {
    class VariableTester final : public Tester {
    public:
        VariableTester() = default;
        ~VariableTester() override = default;

        static void runTests();

    private:
        static void testUniqueId();
        static void testInitialDomain();
        static void testRemoveValueFromDomain();

    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_VARIABLETESTER_H