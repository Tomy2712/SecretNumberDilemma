//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_VARIABLE_H
#define SECRETNUMBERDILEMMA_VARIABLE_H

#include <set>
#include <iostream>

#include "secretNumberDilemma/utils/utils.h"

namespace secretNumberDilemma {
    class Variable {
    public:
        Variable();
        ~Variable();

        uchar getId() const;
        uchar getIdLetter() const;
        std::set<uchar> getDomain() const;

        bool removeValueFromDomain(uchar value);

        bool isSolved() const;

        void display() const;

    private:
        static uchar nombreInstances;
        uchar id;
        std::set<uchar> domain;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_VARIABLE_H