#include "secretNumberDilemma/tests/multiplicativeConstraintTester.h"

namespace secretNumberDilemma {
    void MultiplicativeConstraintTester::runTests() {
        std::cout << "Running MultiplicativeConstraint tests..." << std::endl;
        MultiplicativeConstraintTester::testSingleRemoval();
        std::cout << "ALL MULTIPLICATIVECONSTRAINT TESTS PASSED !\n" << std::endl;
    }

    void MultiplicativeConstraintTester::testSingleRemoval() {
        const auto v1 = new Variable();
        const auto v2 = new Variable();

        for (uchar i = 0; i <= 100; ++i) {
            if (i == 2 || i == 5) continue;
            v1->removeValueFromDomain(i);
        }
        v1->display();
        v2->display();

        MultiplicativeConstraint multiplicativeConstraint(v1, v2, 0);
        const bool res = multiplicativeConstraint.filterDomain();
        assert(res);

        v1->display();
        v2->display();

        delete v1;
        delete v2;
    }

}
