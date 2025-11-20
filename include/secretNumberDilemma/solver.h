#ifndef SECRETNUMBERDILEMMA_SOLVER_H
#define SECRETNUMBERDILEMMA_SOLVER_H

#include <vector>
#include <map>
#include <set>
#include <memory>

#include "csp/variable.h"
#include "csp/cspModel.h"
#include "csp/constraint/additiveConstraint.h"
#include "csp/constraint/multiplicativeConstraint.h"
#include "csp/constraint/divisionConstraint.h"
#include "csp/constraint/zeroConstraint.h"

namespace secretNumberDilemma {
    struct GivenAnswer {
        uchar askerPlayer;
        OperationType operation;
        uchar result;

        GivenAnswer(uchar asker, OperationType op, uchar res)
            : askerPlayer(asker), operation(op), result(res) {}
    };

    struct QuestionOption {
        uchar player1;
        uchar player2;
        OperationType operation;
        uchar result;
        size_t totalDomainSize;
        size_t maxReduction;
        size_t standardDeviation;
        size_t infoLeakage;
        double score;

        QuestionOption(uchar p1, uchar p2, OperationType op, uchar res, size_t totalSize, size_t maxRed, size_t stdDev = 0, size_t leak = 0, double sc = 0.0)
            : player1(p1), player2(p2), operation(op), result(res), totalDomainSize(totalSize), maxReduction(maxRed), standardDeviation(stdDev), infoLeakage(leak), score(sc) {}
    };

    class Solver {
    public:
        Solver(std::vector<std::shared_ptr<Variable>> &variables, CspModel *cspModel, uchar myId);

        std::pair<std::map<uchar, std::vector<std::vector<uchar>>>, std::map<uchar, size_t>>
        simulateQuestion(uchar p1, uchar p2, OperationType op);

        std::vector<QuestionOption> evaluateAllQuestions(size_t topN = 5);

        void recordQuestion(uchar player, OperationType op);
        void recordGivenAnswer(uchar askerPlayer, OperationType op, uchar result);

    private:
        std::vector<std::shared_ptr<Variable>> &variables;
        CspModel *cspModel;
        uchar myId;
        std::set<uchar> questionnedPlayers;
        std::set<std::pair<uchar, OperationType>> askedQuestions;
        std::vector<GivenAnswer> givenAnswers;
        
        std::map<uchar, std::pair<std::vector<uchar>, std::vector<uchar>>> givenDomains;

        std::unique_ptr<Constraint> createConstraint(uchar p1, uchar p2, OperationType op, uchar result);

        size_t calculateTotalDomainSize(const std::vector<std::vector<uchar>>& domains);
        QuestionOption evaluateQuestion(uchar p1, uchar p2, OperationType op);
        uchar calculateResult(uchar val1, uchar val2, OperationType op);
        
        size_t calculateLeak(
            const std::pair<std::vector<uchar>, std::vector<uchar>>& domains,
            OperationType op);
        
        std::vector<uchar> simulateConstraintOnDomain(
            const std::vector<uchar>& domainToFilter,
            const std::vector<uchar>& otherDomain,
            OperationType op,
            uchar result);
    };
}

#endif