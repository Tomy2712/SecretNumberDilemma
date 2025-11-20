//
// Created by Tom on 18/11/2025.
//

#include "secretNumberDilemma/csp/constraint/multiplicativeConstraint.h"

namespace secretNumberDilemma {

    MultiplicativeConstraint::MultiplicativeConstraint(Variable *var1, Variable *var2, uchar res): BinaryConstraint(var1, var2, res) {}

    bool MultiplicativeConstraint::filterDomain() {
        bool modified = false;
        std::vector<uchar> toRemoveV1;
        toRemoveV1.reserve(this->var1->getDomain().size()-1);
        for (const auto & val : this->var1->getDomain()) {
            bool hasFound = false;
            for (const auto & val2 : this->var2->getDomain()) {
                if ((+val * +val2) % 10 == this->res) {
                    hasFound = true;
                    break;
                }
            }
            if (!hasFound) {
                toRemoveV1.push_back(val);
            }
        }

        std::vector<uchar> toRemoveV2;
        toRemoveV2.reserve(this->var2->getDomain().size()-1);
        for (const auto & val : this->var2->getDomain()) {
            bool hasFound = false;
            for (const auto & val2 : this->var1->getDomain()) {
                if ((+val * +val2) % 10 == this->res) {
                    hasFound = true;
                    break;
                }
            }
            if (!hasFound) {
                toRemoveV2.push_back(val);
            }
        }

        for (const auto & val : toRemoveV1) {
            modified |= this->var1->removeValueFromDomain(val);
        }
        for (const auto & val : toRemoveV2) {
            modified |= this->var2->removeValueFromDomain(val);
        }

        return modified;
    }

    bool MultiplicativeConstraint::simulateConstraint(State &state) {
        std::set<uchar>& d1 = state[this->var1->getId()];
        std::set<uchar>& d2 = state[this->var2->getId()];
        bool modified = false;

        std::vector<uchar> toRemoveV1;
        if (d1.size() > 0) {
            toRemoveV1.reserve(d1.size());
        }
        for (const auto & val : d1) {
            bool hasFound = false;
            for (const auto & val2 : d2) {
                if ((+val * +val2) % 10 == this->res) {
                    hasFound = true;
                    break;
                }
            }
            if (!hasFound) {
                toRemoveV1.push_back(val);
            }
        }

        std::vector<uchar> toRemoveV2;
        if (d2.size() > 0) {
            toRemoveV2.reserve(d2.size());
        }
        for (const auto & val : d2) {
            bool hasFound = false;
            for (const auto & val2 : d1) {
                if ((+val * +val2) % 10 == this->res) {
                    hasFound = true;
                    break;
                }
            }
            if (!hasFound) {
                toRemoveV2.push_back(val);
            }
        }

        for (const auto & val : toRemoveV1) {
            if (d1.contains(val)) {
                d1.erase(val);
                modified = true;
            }
        }
        for (const auto & val : toRemoveV2) {
            if (d2.contains(val)) {
                d2.erase(val);
                modified = true;
            }
        }

        return modified;
    }



} // secretNumberDilemma