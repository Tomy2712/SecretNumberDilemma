#include "secretNumberDilemma/tests/divisionConstraintTester.h"

namespace secretNumberDilemma {
    void DivisionConstraintTester::runTests() {
        std::cout << "Running DivisionConstraint tests..." << std::endl;
        testSingleRemoval();
        std::cout << "All DivisionConstraint tests passed!" << std::endl;
    }

    void DivisionConstraintTester::testSingleRemoval() {
        auto *v1 = new Variable();
        auto *v2 = new Variable();

        for (uchar i = 0; i <=100; ++i) {
            if (i == 2 ||i == 10) continue;
            v1->removeValueFromDomain(i);
        }

        for (uchar i = 0; i <=100; ++i) {
            if (i == 25 ) continue;
            v2->removeValueFromDomain(i);
        }

        DivisionConstraint divConstraint(v1, v2, 12);
        const bool modified = divConstraint.filterDomain();

        v1->display();
        v2->display();

        delete v1;
        delete v2;

        std::cout << "\t-Single Removal tests passed!" << std::endl;
    }



}