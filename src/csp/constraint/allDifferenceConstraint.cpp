//
// Created by Tom on 17/11/2025.
//

#include "../../../include/secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

namespace secretNumberDilemma {
    AllDifferenceConstraint::AllDifferenceConstraint(const std::vector<Variable *> &variables) : variables(variables) {}

    bool AllDifferenceConstraint::filterDomain() {
        std::set<unsigned char> valueToRemove;

        for (const auto& variable : this->variables) {
            if (variable->getDomain().size() == 1) {
                valueToRemove.insert(*(variable->getDomain().begin()));
            }
        }
        if (valueToRemove.empty()) {
            return false;
        }
        bool modified = false;
        for (const auto& variable : this->variables) {
            if (variable->getDomain().size() > 1) {
                for (const auto val : valueToRemove) {
                    variable->removeValueFromDomain(val);
                    modified = true;
                }
            }
        }


        return modified;
    }

} // secretNumberDilemma