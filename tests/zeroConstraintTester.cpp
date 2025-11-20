#include "secretNumberDilemma/tests/zeroConstraintTester.h"

namespace secretNumberDilemma {
    void ZeroConstraintTester::runTests() {
        std::cout << "Running ZeroConstraint tests..." << std::endl;
        testSingleRemoval();
        std::cout << "All ZeroConstraint tests passed!" << std::endl;
    }

    void ZeroConstraintTester::testSingleRemoval() {
        auto *v1 = new Variable();
        auto *v2 = new Variable();

        for (uchar i = 0; i <=100; ++i) {
            if (i == 2 ||i == 15) continue;
            v1->removeValueFromDomain(i);
        }

        for (uchar i = 0; i <=100; ++i) {
            if (i == 25 ) continue;
            v2->removeValueFromDomain(i);
        }

        ZeroConstraint zeroConstraint(v1, v2, 2);
        const bool modified = zeroConstraint.filterDomain();
        v1->display();
        v2->display();

        delete v1;
        delete v2;

        std::cout << "\t-Single Removal passed !" << std::endl;
    }
}