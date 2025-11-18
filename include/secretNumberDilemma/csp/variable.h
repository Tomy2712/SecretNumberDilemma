//
// Created by Tom on 17/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_VARIABLE_H
#define SECRETNUMBERDILEMMA_VARIABLE_H

#include <set>
#include <iostream>

namespace secretNumberDilemma {
    class Variable {
    public:
        Variable();
        ~Variable() = default;


        [[nodiscard]] unsigned char getId() const;

        [[nodiscard]] std::set<unsigned char> getDomain() const;

        /**
         * Remove the 'value' from the domain
         * @param value to remove
         * @return true if the value was in the domain and has been removed, false otherwise
         */
        bool removeValueFromDomain(unsigned char value);

        void display() const;

    private:
        static unsigned char nombreInstances;
        unsigned char id;
        std::set<unsigned char> domain;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_VARIABLE_H