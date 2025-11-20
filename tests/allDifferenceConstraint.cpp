#include "secretNumberDilemma/tests/allDifferenceConstraint.h"

namespace secretNumberDilemma {
    void AllDifferenceConstraintTester::runTests() {
        std::cout << "Running AllDifferenceConstraint tests..." << std::endl;
        AllDifferenceConstraintTester::testNoModification();
        AllDifferenceConstraintTester::testSingleRemoval();
        std::cout << "ALL ALLDIFFERENCECONSTRAINT TESTS PASSED !\n" << std::endl;
    }

    void AllDifferenceConstraintTester::testNoModification() {
        std::vector<std::shared_ptr<Variable>> variables;
        variables.reserve(3);

        for (int i = 0; i < 3; ++i) {
            variables.push_back(std::make_shared<Variable>());
        }

        AllDifferenceConstraint allDiffConstraint(variables);
        const bool res = allDiffConstraint.filterDomain();
        assert(!res);

        for (const auto & variable : variables) {
            assert(variable->getDomain().size() == 100);
        }

        std::cout << "\t-No Modification test passed." <<  std::endl;
    }

    void AllDifferenceConstraintTester::testSingleRemoval() {
        std::vector<std::shared_ptr<Variable>> variables;
        variables.reserve(3);

        for (int i = 0; i < 3; ++i) {
            variables.push_back(std::make_shared<Variable>());
        }

        AllDifferenceConstraint allDiffConstraint(variables);
        for (auto i = 0; i <= 100; ++i) {
            if (i == 42) continue;
            variables[0]->removeValueFromDomain(i);
        }
        const bool res = allDiffConstraint.filterDomain();
        assert(res);

        for (const auto & variable : variables) {
            if (variable == variables[0]) continue;
            assert(variable->getDomain().size() == 99);
            assert(!variable->getDomain().contains(42));
        }

        std::cout << "\t-Single Removal test passed." <<  std::endl;
    }

} // secretNumberDilemma