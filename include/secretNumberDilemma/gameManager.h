//
// Created by Tom on 18/11/2025.
//

#ifndef SECRETNUMBERDILEMMA_GAMEMANAGER_H
#define SECRETNUMBERDILEMMA_GAMEMANAGER_H

#include <sstream>
#include <memory>

#include "blackBox.h"
#include "csp/cspModel.h"
#include "utils/utils.h"
#include "csp/constraint/additiveConstraint.h"
#include "csp/constraint/divisionConstraint.h"
#include "csp/constraint/multiplicativeConstraint.h"
#include "csp/constraint/zeroConstraint.h"
#include "solver.h"

namespace secretNumberDilemma {

    struct QuestionRecord {
        uchar player1;
        uchar player2;
        OperationType operation;
        uchar result;
    };

    class GameManager {
    public:
        GameManager(uchar nbPlayer, uchar myId, bool haveBlackBox=false);

        ~GameManager() = default;


        void update();

        [[nodiscard]] bool isGameOver() const;

        [[nodiscard]] std::vector<uchar> getSolution() const;
        
        void displayQuestionHistory();
        void displayCurrentResults();

    private:
        [[nodiscard]] int askBlackBox(uchar p1, uchar p2, OperationType op) const;
        void createAndAddConstraint(uchar p1, uchar p2, OperationType op, int result);
        void displayBestQuestions();
        void handleAnswerQuestion();
        std::string operationToString(OperationType op) const;

        int roundCount = 0;
        uchar nbPlayer;
        uchar myId;
        bool haveBlackBox;
        std::unique_ptr<BlackBox> blackBox;

        std::vector<std::shared_ptr<Variable>> variables;
        std::unique_ptr<CspModel> cspModel;
        std::unique_ptr<Solver> solver;
        std::vector<QuestionRecord> questionHistory;
    };
} // secretNumberDilemma

#endif //SECRETNUMBERDILEMMA_GAMEMANAGER_H