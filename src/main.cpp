//
// Created by Tom on 16/11/2025.
//

#include <iostream>
#include <vector>

#include "../include/secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

int main() {
    std::vector<secretNumberDilemma::Variable*> variables;
    variables.reserve(10); // 10 joueurs

    for (int i = 0; i < variables.capacity(); ++i) {
        variables.push_back(new secretNumberDilemma::Variable());
    }

    for (const auto & variable : variables) {
        variable->display();
    }

    for (int i = 1; i < 101; ++i) {
        if (i == 50) continue;
        variables[0]->removeValueFromDomain(i);
    }



    std::cout << "------------------------------------------------" << std::endl;

    secretNumberDilemma::AllDifferenceConstraint allDiffConstraint(variables);
    const bool res = allDiffConstraint.filterDomain();

    std::cout << res << std::endl;

    for (const auto & variable : variables) {
        variable->display();
    }

    return 0;
}


