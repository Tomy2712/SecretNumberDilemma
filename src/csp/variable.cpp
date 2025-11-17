//
// Created by Tom on 17/11/2025.
//

#include "../../include/secretNumberDilemma/csp/variable.h"

namespace secretNumberDilemma {
    unsigned char Variable::nombreInstances = 0;

    Variable::Variable() {
        this->id = 65 + Variable::nombreInstances++;
        this->domain = std::set<unsigned char>();
        for (unsigned char i = 1; i < 101; ++i) {
            this->domain.insert(i);
        }
    }

    unsigned char Variable::getId() const {
        return this->id;
    }

    std::set<unsigned char> Variable::getDomain() const {
        return this->domain;
    }

    void Variable::removeValueFromDomain(const unsigned char value) {
        if (this->domain.contains(value))
            this->domain.erase(value);
    }

    void Variable::display() const {
        std::cout << "Variable " << this->id << "\ndomain: ";
        for (const int& value : this->domain) {
            std::cout << value << " ";
        }
        std::cout << "\n" << std::endl;
    }


} // secretNumberDilemma