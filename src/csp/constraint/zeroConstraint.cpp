//
// Created by Tom on 18/11/2025.
//

#include "secretNumberDilemma/csp/constraint/zeroConstraint.h"

#include "secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/utils/utils.h"

namespace secretNumberDilemma {
    ZeroConstraint::ZeroConstraint(Variable* variable1, Variable* variable2, const uchar res): BinaryConstraint(variable1, variable2, res) {}

    bool ZeroConstraint::filterDomain() {
        bool modified = false;

        std::vector<uchar> toRemoveV1;
        toRemoveV1.reserve(this->var1->getDomain().size()-1);
        for (const auto & val1 : this->var1->getDomain()) {
            bool hasSupport = false;
            for (const auto & val2 : this->var2->getDomain()) {
                if (ZeroConstraint::countZerosInInterval(val1, val2) == this->res) {
                    hasSupport = true;
                    break;
                }
            }
            if (!hasSupport) {
                toRemoveV1.push_back(val1);
            }
        }

        std::vector<uchar> toRemoveV2;
        toRemoveV2.reserve(this->var2->getDomain().size()-1);
        for (const auto & val2 : this->var2->getDomain()) {
            bool hasSupport = false;
            for (const auto & val1 : this->var1->getDomain()) {
                if (ZeroConstraint::countZerosInInterval(val1, val2) == this->res) {
                    hasSupport = true;
                    break;
                }
            }
            if (!hasSupport) {
                toRemoveV2.push_back(val2);
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

    bool ZeroConstraint::simulateConstraint(State &state) {
        std::set<uchar>& d1 = state[this->var1->getId()];
        std::set<uchar>& d2 = state[this->var2->getId()];
        bool modified = false;

        std::vector<uchar> toRemoveV1;
        if (d1.size() > 0) {
            toRemoveV1.reserve(d1.size());
        }
        for (const auto & val1 : d1) {
            bool hasSupport = false;
            for (const auto & val2 : d2) {
                if (ZeroConstraint::countZerosInInterval(val1, val2) == this->res) {
                    hasSupport = true;
                    break;
                }
            }
            if (!hasSupport) {
                toRemoveV1.push_back(val1);
            }
        }

        std::vector<uchar> toRemoveV2;
        if (d2.size() > 0) {
            toRemoveV2.reserve(d2.size());
        }
        for (const auto & val2 : d2) {
            bool hasSupport = false;
            for (const auto & val1 : d1) {
                if (ZeroConstraint::countZerosInInterval(val1, val2) == this->res) {
                    hasSupport = true;
                    break;
                }
            }
            if (!hasSupport) {
                toRemoveV2.push_back(val2);
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

    uchar ZeroConstraint::countZerosInInterval(const uchar val1, const uchar val2) {
        uchar count = 0;
        const uchar start = std::min(val1, val2);
        const uchar end = std::max(val1, val2);

        uchar current = (start % 10 == 0) ? start : (start - (start % 10) + 10);
        while (current <= end) {
            if (current == 100) {
                count+=2;
            } else {
                count++;
            }
            current += 10;
        }
        return count;
    }

}
