#include "secretNumberDilemma/csp/variable.h"

namespace secretNumberDilemma {
    unsigned char Variable::nombreInstances = 0;

    Variable::Variable() {
        this->id = Variable::nombreInstances++;
        this->domain = std::set<uchar>();
        for (uchar i = 1; i <= 100; ++i) {
            this->domain.insert(i);
        }
    }

    Variable::~Variable() {
        Variable::nombreInstances--;
    }

    uchar Variable::getId() const {
        return this->id;
    }

    uchar Variable::getIdLetter() const {
        return 65 + this->id;
    }

    std::set<uchar> Variable::getDomain() const {
        return this->domain;
    }

    bool Variable::removeValueFromDomain(const uchar value) {
        if (this->domain.contains(value)) {
            this->domain.erase(value);
            return true;
        }
        return false;
    }

    bool Variable::isSolved() const {
        return this->domain.size() == 1;
    }

    void Variable::display() const {
        std::cout << this->getIdLetter() << " : ";
        if (this->domain.empty()) return;

        auto it = this->domain.begin();
        unsigned char start = *it;
        unsigned char prev = *it;
        ++it;

        for (; it != this->domain.end(); ++it) {
            if (*it == prev + 1) {
                prev = *it;
            } else {
                if (start == prev)
                    std::cout << +start << " ";
                else
                    std::cout << +start << "-" << +prev << " ";
                start = prev = *it;
            }
        }

        // dernier sous-ensemble
        if (start == prev)
            std::cout << +start;
        else
            std::cout << +start << "-" << +prev;

        std::cout << " (size:" << this->domain.size() << ")" << std::endl;
    }


} // secretNumberDilemma