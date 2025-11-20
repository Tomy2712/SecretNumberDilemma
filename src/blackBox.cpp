#include "secretNumberDilemma/blackBox.h"

namespace secretNumberDilemma {
    BlackBox::BlackBox(const uchar nbPlayer) : nbPlayer(nbPlayer) {
        std::uniform_int_distribution<> distrib(1, 100);

        std::set<uchar> uniqueNumbers;

        while (uniqueNumbers.size() < nbPlayer) {
            auto randomNumber = static_cast<uchar>(distrib(this->gen));
            uniqueNumbers.insert(randomNumber);
        }
        this->secretNumbers.assign(uniqueNumbers.begin(), uniqueNumbers.end());
    }

    void BlackBox::displaySecretNumbers() const {
        for (auto i=0; i < this->nbPlayer; ++i) {
            std::cout << "" << static_cast<char>(65 + i) << " = " << static_cast<int>(this->secretNumbers[i]) << " | ";
        }
        std::cout << std::endl;
    }

    int BlackBox::getAdditiveResult(const uchar j1, const uchar j2) {
        const int sum = secretNumbers[j1] + secretNumbers[j2];
        if (sum <= 20) {
            std::uniform_int_distribution<> distrib(3, 20);
            return distrib(this->gen);
        } else if (sum >=180) {
            std::uniform_int_distribution<> distrib(180, 199);
            return distrib(this->gen);
        } else {
            return sum;
        }
    }

    int BlackBox::getMultiplicativeResult(const uchar j1, const uchar j2) const {
        return (secretNumbers[j1] * secretNumbers[j2]) % 10;
    }

    int BlackBox::getDivisionResult(const uchar j1, const uchar j2) const {
        const uchar s1 = secretNumbers[j1];
        const uchar s2 = secretNumbers[j2];
        return std::max(s1, s2) / std::min(s1, s2);
    }

    int BlackBox::getZeroResult(const uchar j1, const uchar j2) const {
        uchar count = 0;
        const uchar val1 = secretNumbers[j1];
        const uchar val2 = secretNumbers[j2];
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

} // secretNumberDilemma