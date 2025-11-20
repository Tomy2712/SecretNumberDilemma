#include "secretNumberDilemma/tests/additiveConstraintTester.h"

#include "secretNumberDilemma/csp/variable.h"

namespace secretNumberDilemma {
    void AdditiveConstraintTester::runTests() {
        std::cout << "Running AdditiveConstraint tests..." << std::endl;
        AdditiveConstraintTester::testSingleRemoval();
        std::cout << "ALL ADDITIVECONSTRAINT TESTS PASSED !\n" << std::endl;
    }


    void AdditiveConstraintTester::testSingleRemoval() {
        auto v1 = new Variable();
        auto v2 = new Variable();

        v1->removeValueFromDomain(1);
        v1->removeValueFromDomain(2);
        v1->removeValueFromDomain(3);

        AdditiveConstraint additiveConstraint(v1, v2, 5);
        const bool res = additiveConstraint.filterDomain();
        assert(res);

        v1->display();
        v2->display();

        delete v1;
        delete v2;

        v1 = new Variable();
        v2 = new Variable();

        v1->removeValueFromDomain(100);
        v1->removeValueFromDomain(99);
        v1->removeValueFromDomain(98);

        AdditiveConstraint additiveConstraint2(v1, v2, 185);
        const bool res2 = additiveConstraint2.filterDomain();
        assert(res2);
        v1->display();
        v2->display();
        delete v1;
        delete v2;


        v1 = new Variable();
        v2 = new Variable();
        v1->removeValueFromDomain(10);
        v1->removeValueFromDomain(16);
        v2->removeValueFromDomain(6);
        v2->removeValueFromDomain(24);

        AdditiveConstraint additiveConstraint3(v1, v2, 25);
        const bool res3 = additiveConstraint3.filterDomain();
        assert(res3);
        v1->display();
        v2->display();
        delete v1;
        delete v2;


        std::cout << "\t-Single Removal test passed." <<  std::endl;
    }
}