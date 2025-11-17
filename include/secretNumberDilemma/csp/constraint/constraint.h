//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_CONSTRAINT_H
#define SECRETNUMBERDILEMMA_CONSTRAINT_H

namespace secretNumberDilemma {
    class Constraint {
    public:
        virtual ~Constraint() = default;

        /**
         * Reduced domains of the variables
         * @return true if there is a modification, false otherwise
         */
        virtual bool filterDomain() = 0;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_CONSTRAINT_H