//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_TESTER_H
#define SECRETNUMBERDILEMMA_TESTER_H

#include <cassert>
#include <iostream>

namespace secretNumberDilemma {
    class Tester {
        public :
            Tester() = default;

            virtual ~Tester() = default;

           static void runTests();
    };
} // secretNumberDilemma


#endif //SECRETNUMBERDILEMMA_TESTER_H