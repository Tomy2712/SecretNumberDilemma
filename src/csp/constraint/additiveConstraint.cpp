//
// Created by Tom on 18/11/2025.
//

#include "secretNumberDilemma/csp/constraint/additiveConstraint.h"

namespace secretNumberDilemma {
    AdditiveConstraint::AdditiveConstraint(Variable *v1, Variable *v2, const uchar res): BinaryConstraint(v1, v2, res) {}

    bool AdditiveConstraint::filterDomain() {
        bool modified = false;
        if (this->res <= 20) {
            const uchar maxToKeepV1 = 20 - *this->var2->getDomain().begin();
            const uchar maxToKeepV2 = 20 - *this->var1->getDomain().begin();

            for (uchar val = maxToKeepV1 + 1; val <= 100; ++val)
                modified |= this->var1->removeValueFromDomain(val);

            for (uchar val = maxToKeepV2 + 1; val <= 100; ++val)
                modified |= this->var2->removeValueFromDomain(val);
        } else if (this->res >= 180){
            const uchar minToKeepV1 = 180 - *this->var2->getDomain().rbegin();
            const uchar minToKeepV2 = 180 - *this->var1->getDomain().rbegin();

            for (uchar val = 1; val < minToKeepV1; ++val)
                modified |= this->var1->removeValueFromDomain(val);

            for (uchar val = 1; val < minToKeepV2; ++val)
                modified |= this->var2->removeValueFromDomain(val);

        } else {
            std::vector<uchar> toRemoveV1;
            toRemoveV1.reserve(this->var1->getDomain().size()-1);
            for (const auto & val : this->var1->getDomain()) {
                bool hasFound = false;
                if (this->var2->getDomain().contains(this->res - val)) {
                    hasFound = true;
                }
                if (!hasFound) {
                    toRemoveV1.push_back(val);
                }
            }

            std::vector<uchar> toRemoveV2;
            toRemoveV2.reserve(this->var2->getDomain().size()-1);
            for (const auto & val : this->var2->getDomain()) {
                bool hasFound = false;
                if (this->var1->getDomain().contains(this->res - val)) {
                    hasFound = true;
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
        }
        return modified;
    }


    bool AdditiveConstraint::simulateConstraint(State &state) {
        std::set<uchar>& d1 = state[this->var1->getId()];
        std::set<uchar>& d2 = state[this->var2->getId()];
        bool modified = false;
        if (this->res <= 20) {
            const uchar maxToKeepV1 = 20 - *d2.begin();
            const uchar maxToKeepV2 = 20 - *d1.begin();

            for (uchar val = maxToKeepV1 + 1; val <= 100; ++val) {
                if (d1.contains(val)) {
                    d1.erase(val);
                    modified = true;
                }
            }

            for (uchar val = maxToKeepV2 + 1; val <= 100; ++val)
                if (d2.contains(val)) {
                    d2.erase(val);
                    modified = true;
                }
        } else if (this->res >= 180){
            const uchar minToKeepV1 = 180 - *d2.rbegin();
            const uchar minToKeepV2 = 180 - *d1.rbegin();

            for (uchar val = 1; val < minToKeepV1; ++val) {
                if (d1.contains(val)) {
                    d1.erase(val);
                    modified = true;
                }
            }

            for (uchar val = 1; val < minToKeepV2; ++val) {
                if (d2.contains(val)) {
                    d2.erase(val);
                    modified = true;
                }
            }

        } else {
            std::vector<uchar> toRemoveV1;
            if (d1.size() > 0) {
                toRemoveV1.reserve(d1.size());
            }
            for (const auto & val : d1) {
                bool hasFound = false;
                if (d2.contains(this->res - val)) {
                    hasFound = true;
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
                if (d1.contains(this->res - val)) {
                    hasFound = true;
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
        }
        return modified;
    }

} // secretNumberDilemma