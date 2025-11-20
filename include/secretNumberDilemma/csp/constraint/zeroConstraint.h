//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_ZEROCONSTRAINT_H
#define SECRETNUMBERDILEMMA_ZEROCONSTRAINT_H

#include <algorithm>

#include "binaryConstraint.h"

namespace secretNumberDilemma {
    class ZeroConstraint final : public BinaryConstraint {
    public:
        ZeroConstraint(Variable* variable1, Variable* variable2, uchar res);

        bool filterDomain() override;
        bool simulateConstraint(State &state) override;
    private:
        static uchar countZerosInInterval(const uchar val1, const uchar val2);
    };
}



#endif //SECRETNUMBERDILEMMA_ZEROCONSTRAINT_H