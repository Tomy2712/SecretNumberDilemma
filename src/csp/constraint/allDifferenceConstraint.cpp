//
// Created by Tom on 17/11/2025.
//

#include "secretNumberDilemma/csp/constraint/allDifferenceConstraint.h"

namespace secretNumberDilemma {
    AllDifferenceConstraint::AllDifferenceConstraint(const std::vector<std::shared_ptr<Variable>> &variables) : variables(variables) {}


    bool AllDifferenceConstraint::filterDomain() {
        std::set<uchar> valueToRemove;

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
                    modified |= variable->removeValueFromDomain(val);
                }
            }
        }


        return modified;
    }

    bool AllDifferenceConstraint::simulateConstraint(State &state) {
        std::set<uchar> valueToRemove;

        for (auto &stateDomains : state) {
            if (stateDomains.size() == 1) {
                valueToRemove.insert(*(stateDomains.begin()));
            }
        }
        if (valueToRemove.empty()) {
            return false;
        }

        bool modified = false;
        for (auto &stateDomains : state) {
            if (stateDomains.size() > 1) {
                for (const uchar val : valueToRemove) {
                    if (stateDomains.contains(val)) {
                        stateDomains.erase(val);
                        modified = true;
                    }
                }
            }
        }

        return modified;
    }

} // secretNumberDilemma