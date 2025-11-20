#include "secretNumberDilemma/tests/additiveConstraintTester.h"
#include "secretNumberDilemma/tests/variableTester.h"
#include "secretNumberDilemma/tests/allDifferenceConstraint.h"
#include "secretNumberDilemma/tests/divisionConstraintTester.h"
#include "secretNumberDilemma/tests/multiplicativeConstraintTester.h"
#include "secretNumberDilemma/tests/zeroConstraintTester.h"

int main() {
    secretNumberDilemma::VariableTester::runTests();
    secretNumberDilemma::AllDifferenceConstraintTester::runTests();
    secretNumberDilemma::AdditiveConstraintTester::runTests();
    secretNumberDilemma::MultiplicativeConstraintTester::runTests();
    secretNumberDilemma::DivisionConstraintTester::runTests();
    secretNumberDilemma::ZeroConstraintTester::runTests();
    return 0;
}


