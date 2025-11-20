#include "secretNumberDilemma/solver.h"
#include <algorithm>
#include <memory>
#include <cmath>

namespace secretNumberDilemma {

    Solver::Solver(std::vector<std::shared_ptr<Variable>> &variables, CspModel *cspModel, uchar myId)
        : variables(variables), cspModel(cspModel), myId(myId) {
        const auto& myDomain = variables[myId]->getDomain();
        for (size_t i = 0; i < variables.size(); ++i) {
            if (i != myId) {
                std::vector<uchar> myDomainCopy(myDomain.begin(), myDomain.end());
                const auto& theirDomain = variables[i]->getDomain();
                std::vector<uchar> theirDomainCopy(theirDomain.begin(), theirDomain.end());
                this->givenDomains[i] = {myDomainCopy, theirDomainCopy};
            }
        }
    }

    void Solver::recordQuestion(uchar player, OperationType op) {
        this->questionnedPlayers.insert(player);
        this->askedQuestions.insert({player, op});
    }

    void Solver::recordGivenAnswer(uchar askerPlayer, OperationType op, uchar result) {
        this->givenAnswers.push_back(GivenAnswer(askerPlayer, op, result));
        
        auto& [myDomain, playerDomain] = this->givenDomains[askerPlayer];
        
        
        std::vector<uchar> newMyDomain = this->simulateConstraintOnDomain(
            myDomain, playerDomain, op, result
        );
        
        myDomain = newMyDomain;
        
        const auto& playerCurrentDomain = this->variables[askerPlayer]->getDomain();
        std::vector<uchar> updatedPlayerDomain;
        for (uchar val : playerDomain) {
            if (playerCurrentDomain.find(val) != playerCurrentDomain.end()) {
                updatedPlayerDomain.push_back(val);
            }
        }
        playerDomain = updatedPlayerDomain;
    }
    
    std::vector<uchar> Solver::simulateConstraintOnDomain(
        const std::vector<uchar>& domainToFilter,
        const std::vector<uchar>& otherDomain,
        OperationType op,
        uchar result) {
        
        std::vector<uchar> filteredDomain;
        
        for (uchar val : domainToFilter) {
            bool compatible = false;
            
            for (uchar otherVal : otherDomain) {
                uchar computed = this->calculateResult(otherVal, val, op);
                if (computed == result) {
                    compatible = true;
                    break;
                }
            }
            
            if (compatible) {
                filteredDomain.push_back(val);
            }
        }
        
        return filteredDomain;
    }

    std::unique_ptr<Constraint> Solver::createConstraint(uchar p1, uchar p2, OperationType op, uchar result) {
        switch (op) {
            case OperationType::SUM:
                return std::make_unique<AdditiveConstraint>(this->variables[p1].get(), this->variables[p2].get(), result);
            case OperationType::MUL:
                return std::make_unique<MultiplicativeConstraint>(this->variables[p1].get(), this->variables[p2].get(), result);
            case OperationType::DIV:
                return std::make_unique<DivisionConstraint>(this->variables[p1].get(), this->variables[p2].get(), result);
            case OperationType::ZEROCOUNT:
                return std::make_unique<ZeroConstraint>(this->variables[p1].get(), this->variables[p2].get(), result);
            default:
                return nullptr;
        }
    }

    size_t Solver::calculateTotalDomainSize(const std::vector<std::vector<uchar>>& domains) {
        size_t total = 0;
        for (const auto& domain : domains) {
            total += domain.size();
        }
        return total;
    }

    uchar Solver::calculateResult(uchar val1, uchar val2, OperationType op) {
        switch (op) {
            case OperationType::SUM: {
                const uchar sum = val1 + val2;
                if (sum <= 20) return 20;
                if (sum >= 180) return 180;
                return sum;
            }

            case OperationType::MUL:
                return static_cast<uchar>((+val1 * +val2) % 10);

            case OperationType::DIV:
                if (std::min(val1, val2) == 0) return 0;
                return std::max(val1, val2) / std::min(val1, val2);

            case OperationType::ZEROCOUNT: {
                uchar start = std::min(val1, val2);
                uchar end = std::max(val1, val2);
                uchar count = 0;
                uchar current = (start % 10 == 0) ? start : (start - (start % 10) + 10);
                while (current <= end) {
                    count += (current == 100) ? 2 : 1;
                    current += 10;
                }
                return count;
            }
        }
        return 0;
    }

    std::pair<std::map<uchar, std::vector<std::vector<uchar>>>, std::map<uchar, size_t>>
        Solver::simulateQuestion(uchar p1, uchar p2, OperationType op) {

        std::map<uchar, std::vector<std::vector<uchar>>> results;
        std::map<uchar, size_t> counts;

        const auto& domain1 = this->variables[p1]->getDomain();
        const auto& domain2 = this->variables[p2]->getDomain();

        for (const auto& val1 : domain1) {
            for (const auto& val2 : domain2) {
                uchar res = this->calculateResult(val1, val2, op);
                counts[res]++;
            }
        }

        for (const auto& [result, count] : counts) {
            auto constraint = this->createConstraint(p1, p2, op, result);
            if (constraint) {
                results[result] = this->cspModel->simulateConstraint(constraint.get());
            }
        }

        return {results, counts};
    }

    QuestionOption Solver::evaluateQuestion(uchar p1, uchar p2, OperationType op) {
        auto [simulations, counts] = this->simulateQuestion(p1, p2, op);

        if (simulations.empty()) {
            return QuestionOption(p1, p2, op, 0, 999999, 0, 999);
        }

        size_t totalReductionWeighted = 0;
        size_t totalOccurrences = 0;
        size_t currentTotalSize = 0;
        std::vector<size_t> reductions;

        for (const auto& var : this->variables) {
            currentTotalSize += var->getDomain().size();
        }

        size_t instantWinWeight = 0;

        for (const auto& [result, domains] : simulations) {
            size_t simulatedSize = this->calculateTotalDomainSize(domains);
            size_t reduction = (currentTotalSize - simulatedSize);
            size_t weight = counts[result];

            totalReductionWeighted += (reduction * weight);
            totalOccurrences += weight;
            
            for (size_t i = 0; i < weight; ++i) {
                reductions.push_back(reduction);
            }
        }

        size_t avgReduction = (totalOccurrences > 0) ? (totalReductionWeighted / totalOccurrences) : 0;

        double variance = 0.0;
        for (size_t red : reductions) {
            double diff = static_cast<double>(red) - static_cast<double>(avgReduction);
            variance += diff * diff;
        }
        variance /= totalOccurrences;
        size_t stdDev = static_cast<size_t>(std::sqrt(variance));

        size_t avgSize = currentTotalSize - avgReduction;
        
        size_t infoLeak = 0;
        if (this->givenDomains.find(p2) != this->givenDomains.end() && 
            this->givenDomains.at(p2).first.size() > 1) {
            infoLeak = this->calculateLeak(this->givenDomains.at(p2), op);
        }
        
        const double W_REDUCTION = 0.7;
        const double W_STDDEV = 0.2;
        const double W_LEAKAGE = 0.1;
        double calculatedScore = (avgReduction * W_REDUCTION)
                               - (stdDev * W_STDDEV)
                               - (infoLeak * W_LEAKAGE);

        return QuestionOption(p1, p2, op, 0, avgSize, avgReduction, stdDev, infoLeak, calculatedScore);
    }
    
    size_t Solver::calculateLeak(
        const std::pair<std::vector<uchar>, std::vector<uchar>>& domains,
        OperationType op) {
        
        const auto& [myDomain, playerDomain] = domains;
        
        size_t currentTotal = myDomain.size() + playerDomain.size();
        
        std::map<uchar, size_t> counts;
        for (uchar myVal : myDomain) {
            for (uchar pVal : playerDomain) {
                uchar result = this->calculateResult(myVal, pVal, op);
                counts[result]++;
            }
        }
        
        std::map<uchar, size_t> totalSizePerResult;
        
        for (const auto& [result, count] : counts) {
            std::vector<uchar> newMyDomain = this->simulateConstraintOnDomain(
                myDomain, playerDomain, op, result
            );
            
            std::vector<uchar> newPlayerDomain = this->simulateConstraintOnDomain(
                playerDomain, myDomain, op, result
            );
            
            size_t newTotal = newMyDomain.size() + newPlayerDomain.size();
            totalSizePerResult[result] = newTotal;
        }
        
        size_t totalReductionWeighted = 0;
        size_t totalOccurrences = 0;
        
        for (const auto& [result, newSize] : totalSizePerResult) {
            size_t reduction = currentTotal - newSize;
            size_t weight = counts[result];
            totalReductionWeighted += (reduction * weight);
            totalOccurrences += weight;
        }
        
        return totalOccurrences > 0 ? totalReductionWeighted / totalOccurrences : 0;
    }

    std::vector<QuestionOption> Solver::evaluateAllQuestions(size_t topN) {
        std::vector<QuestionOption> allOptions;

        const std::vector<OperationType> operations = {
            OperationType::SUM, OperationType::MUL,
            OperationType::DIV, OperationType::ZEROCOUNT
        };

        for (uchar p2 = 0; p2 < this->variables.size(); ++p2) {
            if (p2 == this->myId || this->variables[p2]->getDomain().size() == 1) continue;

            for (const auto& op : operations) {
                if (this->askedQuestions.count({p2, op}) > 0) continue;

                allOptions.push_back(this->evaluateQuestion(this->myId, p2, op));
            }
        }

        std::sort(allOptions.begin(), allOptions.end(),
                [](const QuestionOption& a, const QuestionOption& b) {
                    return a.score > b.score;
                });
        
        size_t n = std::min(topN, allOptions.size());
        return std::vector<QuestionOption>(allOptions.begin(), allOptions.begin() + n);
    }
}