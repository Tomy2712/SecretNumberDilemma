//
// Created by Tom on 16/11/2025.
//

#include <iostream>
#include <vector>

#include "../include/secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

int main() {
    std::cout << "=== Secret Number Dilemma CSP Solver Demo ===" << std::endl;
    std::cout << std::endl;

    // Create three variables
    secretNumberDilemma::Variable var1;
    secretNumberDilemma::Variable var2;
    secretNumberDilemma::Variable var3;

    std::cout << "Initial variables with full domains (1-100):" << std::endl;
    var1.display();
    var2.display();
    var3.display();

    // Reduce domains manually to demonstrate
    std::cout << "Reducing var1's domain to only {50}:" << std::endl;
    for (unsigned char i = 1; i <= 100; ++i) {
        if (i != 50) {
            var1.removeValueFromDomain(i);
        }
    }
    var1.display();

    // Create an AllDifferenceConstraint
    std::vector<secretNumberDilemma::Variable*> variables = {&var1, &var2, &var3};
    secretNumberDilemma::AllDifferenceConstraint constraint(variables);

    std::cout << "Applying AllDifferenceConstraint (all variables must have different values):" << std::endl;
    bool modified = constraint.filterDomain();
    
    if (modified) {
        std::cout << "Domains were modified by the constraint!" << std::endl;
        std::cout << "\nAfter constraint propagation:" << std::endl;
        var1.display();
        var2.display();
        var3.display();
        std::cout << "Note: Value 50 has been removed from var2 and var3 domains." << std::endl;
    } else {
        std::cout << "No modifications were made." << std::endl;
    }

    return 0;
}


