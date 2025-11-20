//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_BLACKBOX_H
#define SECRETNUMBERDILEMMA_BLACKBOX_H

#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

#include "utils/utils.h"

namespace secretNumberDilemma {
    class BlackBox {
    public:
        explicit BlackBox(uchar nbPlayer);

        void displaySecretNumbers() const;

        int getAdditiveResult(uchar j1, uchar j2);
        int getMultiplicativeResult(uchar j1, uchar j2) const;
        int getDivisionResult(uchar j1, uchar j2) const;
        int getZeroResult(uchar j1, uchar j2) const;
    private:
        uchar nbPlayer;
        std::vector<uchar> secretNumbers;
        std::mt19937 gen{std::random_device{}()};
    };
}



#endif //SECRETNUMBERDILEMMA_BLACKBOX_H