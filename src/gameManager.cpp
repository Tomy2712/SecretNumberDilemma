#include "secretNumberDilemma/gameManager.h"
#include <iomanip>

namespace secretNumberDilemma {
    GameManager::GameManager(const uchar nbPlayer, const uchar myId, const bool haveBlackBox):
    nbPlayer(nbPlayer), myId(myId), haveBlackBox(haveBlackBox) {
        if (haveBlackBox)
            this->blackBox = std::make_unique<BlackBox>(nbPlayer);


        this->variables.reserve(nbPlayer);
        for (int i = 0; i < nbPlayer; ++i)
            this->variables.push_back(std::make_shared<secretNumberDilemma::Variable>());

        this->cspModel = std::make_unique<CspModel>(this->variables);
        this->solver = std::make_unique<Solver>(this->variables, this->cspModel.get(), myId);
    }

    std::string GameManager::operationToString(OperationType op) const {
        switch (op) {
            case OperationType::SUM: return "+";
            case OperationType::MUL: return "*";
            case OperationType::DIV: return "%";
            case OperationType::ZEROCOUNT: return "0";
            default: return "?";
        }
    }

    void GameManager::displayBestQuestions() {
        std::cout << "\n+--------------------------------------------------------+" << std::endl;
        std::cout << "|      BEST QUESTIONS (from best to worst)              |" << std::endl;
        std::cout << "+--------------------------------------------------------+" << std::endl;
        
        auto bestQuestions = this->solver->evaluateAllQuestions(36);
        
        if (bestQuestions.empty()) {
            std::cout << "No questions available." << std::endl;
            return;
        }
        
        std::vector<std::pair<QuestionOption, std::vector<uchar>>> groupedQuestions;
        
        for (const auto& q : bestQuestions) {
            bool found = false;
            
            // Chercher un groupe avec les mêmes métriques et opération
            for (auto& group : groupedQuestions) {
                const auto& representative = group.first;
                if (representative.operation == q.operation &&
                    representative.maxReduction == q.maxReduction &&
                    representative.totalDomainSize == q.totalDomainSize &&
                    representative.standardDeviation == q.standardDeviation) {
                    
                    group.second.push_back(q.player2);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                groupedQuestions.push_back({q, {q.player2}});
            }
        }
        
        size_t displayCount = std::min(size_t(9), groupedQuestions.size());
        
        for (size_t i = 0; i < displayCount; ++i) {
            const auto& [representative, players] = groupedQuestions[i];
            
            std::string indicator = (i == 0) ? " > " : "  ";
            
            std::cout << indicator << (i+1) << ". ";
            
            // Afficher les joueurs
            if (players.size() == 1) {
                std::cout << "Player " << static_cast<char>('A' + players[0]);
            } else if (players.size() == this->nbPlayer - 1) {
                // Si tous les joueurs sauf nous, dire "Any player"
                std::cout << "Any player";
            } else {
                std::cout << "Player ";
                for (size_t j = 0; j < players.size(); ++j) {
                    if (j > 0) std::cout << "/";
                    std::cout << static_cast<char>(65+ players[j]);
                }
            }
            
            std::cout << " " << operationToString(representative.operation);
            
            std::string opName;
            switch (representative.operation) {
                case OperationType::SUM: opName = "(sum)"; break;
                case OperationType::MUL: opName = "(product)"; break;
                case OperationType::DIV: opName = "(quotient)"; break;
                case OperationType::ZEROCOUNT: opName = "(zeros)"; break;
            }
            
            // Utiliser setw pour aligner les colonnes
            std::cout << " " << std::left << std::setw(15) << opName
                     << " | red:" << std::right << std::setw(3) << representative.maxReduction 
                     << " sd:" << std::right << std::setw(3) << representative.standardDeviation
                     << " leak:" << std::right << std::setw(3) << representative.infoLeakage
                     << " score:" << std::right << std::setw(5) << static_cast<int>(representative.score);
            
            if (i == 0) {
                std::cout << " * RECOMMENDED";
            }
            std::cout << std::endl;
        }
        std::cout << "\nLegend: red=avg reduction (higher=better)," << std::endl;
        std::cout << "        sd=std deviation (lower=better, more predictable)," << std::endl;
        std::cout << "        leak=info revealed to others (lower=better)," << std::endl;
        std::cout << "        score=final score (higher=better)" << std::endl;
        std::cout << "You are Player " << static_cast<char>(65 + this->myId) << std::endl;
        std::cout << std::endl;
    }

    void GameManager::update() {
        // Afficher domaines
        for (const auto &var : this->variables) {
            var->display();
        }

        std::string input;
        if (this->haveBlackBox)
            this->blackBox->displaySecretNumbers();
        std::cout << "Round " << this->roundCount << std::endl;
        
        // Afficher les meilleures questions
        displayBestQuestions();

        std::getline(std::cin, input);

        if (input == "exit")
            return;
        
        if (input == "answer" || input == "a") {
            this->handleAnswerQuestion();
            return;
        }
        
        if (input == "stop" || input == "s") {
            this->displayCurrentResults();
            return;
        }

        if (input == "help") {
            std::cout << "B:1 | C:2 | D:3 | E:4 | F:5 | G:6 | H:7 | I:8 | J:9" << std::endl;
            std::cout << "\nAvailable commands:" << std::endl;
            std::cout << "  [player] [op] - Ask a question (e.g. 'B +', '1 *')" << std::endl;
            std::cout << "  answer / a    - Record an answer you gave to another player" << std::endl;
            std::cout << "  stop / s      - Display current partial results" << std::endl;
            std::cout << "  help          - Display this help" << std::endl;
            std::cout << "  exit          - Quit the game" << std::endl;
            std::cout << "\nOperations:" << std::endl;
            std::cout << "  + : Sum (result between 2 and 200)" << std::endl;
            std::cout << "  * : Multiplication (last digit of product)" << std::endl;
            std::cout << "  % : Division (quotient of max/min)" << std::endl;
            std::cout << "  0 : Count zeros between the two numbers" << std::endl;
            return;
        }

        std::string p2Str;
        char opChar;
        std::stringstream ss(input);
        if (!(ss >> p2Str >> opChar)) {
            std::cout << "Invalid format" << std::endl;
            return;
        }

        int p2 = 0;
        if (p2Str.length() == 1 && std::isalpha(p2Str[0])) {
            p2 = std::toupper(p2Str[0]) - 'A';
        } else {
            ss.clear();
            ss.str(p2Str);
            if (!(ss >> p2)) {
                std::cout << "Invalid number" << std::endl;
                return;
            }
        }
        if (p2 == this->myId) {
            std::cout << "You cannot use your own ID." << std::endl;
            return;
        }

        OperationType op;
        switch (opChar) {
            case '+': op = OperationType::SUM; break;
            case '*': op = OperationType::MUL; break;
            case '%': op = OperationType::DIV; break;
            case '0': op = OperationType::ZEROCOUNT; break;
            default:
                std::cout << "Invalid operation" << std::endl;
                return;
        }

        int result = 0;
        if (this->haveBlackBox) {
            // normal mode
            result = this->askBlackBox(this->myId, p2, op);
        } else {
            // manual mode
            std::cout << "Enter the result manually: ";
            std::string resStr;
            std::getline(std::cin, resStr);
            std::stringstream rss(resStr);
            if (!(rss >> result)) {
                std::cout << "Invalid result" << std::endl;
                return;
            }
        }

        this->createAndAddConstraint(this->myId, p2, op, result);
        this->solver->recordQuestion(p2, op);
        
        questionHistory.push_back({this->myId, static_cast<uchar>(p2), op, static_cast<uchar>(result)});
        
        std::cout << "Result = " << result << std::endl << std::endl;
    }

    bool GameManager::isGameOver() const {
        for (const auto &var : this->variables) {
            if (!var->isSolved()) {
                return false;
            }
        }
        return true;
    }

    void GameManager::displayQuestionHistory() {
        std::cout << "\n============================================" << std::endl;
        std::cout << "         QUESTION HISTORY" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "Total questions asked: " << questionHistory.size() << std::endl;
        std::cout << "\nAll questions:" << std::endl;
        
        for (size_t i = 0; i < questionHistory.size(); ++i) {
            const auto& q = questionHistory[i];
            std::cout << "  " << (i+1) << ". Player " << static_cast<char>('A' + q.player1)
                     << " " << operationToString(q.operation) << " Player "
                     << static_cast<char>('A' + q.player2)
                     << " = " << static_cast<int>(q.result) << std::endl;
        }
        std::cout << "============================================" << std::endl;
    }

    std::vector<uchar> GameManager::getSolution() const {
        std::vector<uchar> solution;
        solution.reserve(this->nbPlayer);
        for (const auto &var : this->variables) {
            if (var->getDomain().size() == 1) {
                solution.push_back(*(var->getDomain().begin()));
            } else {
                solution.push_back(0);
            }
        }
        return solution;
    }


    int GameManager::askBlackBox(const uchar p1, const uchar p2, const OperationType op) const {
        switch (op) {
            case OperationType::SUM:
                return this->blackBox->getAdditiveResult(p1, p2);
            case OperationType::MUL:
                return this->blackBox->getMultiplicativeResult(p1, p2);
            case OperationType::DIV:
                return this->blackBox->getDivisionResult(p1, p2);
            case OperationType::ZEROCOUNT:
                return this->blackBox->getZeroResult(p1, p2);
            default:
                return -1;
        }
    }

    void GameManager::handleAnswerQuestion() {
        std::cout << "\n=== Record an answer you gave ===" << std::endl;
        
        std::cout << "Which player asked you? (0-" << (this->nbPlayer - 1) << "): ";
        std::string askerStr;
        std::getline(std::cin, askerStr);
        std::stringstream askerSS(askerStr);
        int asker;
        if (!(askerSS >> asker) || asker < 0 || asker >= this->nbPlayer || asker == this->myId) {
            std::cout << "Invalid player" << std::endl;
            return;
        }
        
        std::cout << "Operation (+, *, %, 0): ";
        std::string opStr;
        std::getline(std::cin, opStr);
        if (opStr.empty()) {
            std::cout << "Invalid operation" << std::endl;
            return;
        }
        char opChar = opStr[0];
        
        OperationType op;
        switch (opChar) {
            case '+': op = OperationType::SUM; break;
            case '*': op = OperationType::MUL; break;
            case '%': op = OperationType::DIV; break;
            case '0': op = OperationType::ZEROCOUNT; break;
            default:
                std::cout << "Invalid operation" << std::endl;
                return;
        }
        
        int result = 0;
        if (this->haveBlackBox) {
            result = this->askBlackBox(asker, this->myId, op);
            std::cout << "The result was: " << result << std::endl;
        } else {
            std::cout << "What result did you give? ";
            std::string resStr;
            std::getline(std::cin, resStr);
            std::stringstream resSS(resStr);
            if (!(resSS >> result)) {
                std::cout << "Invalid result" << std::endl;
                return;
            }
        }
        
        this->solver->recordGivenAnswer(asker, op, static_cast<uchar>(result));
        
        this->createAndAddConstraint(asker, this->myId, op, result);
        
        // Enregistrer dans l'historique
        questionHistory.push_back({static_cast<uchar>(asker), this->myId, op, static_cast<uchar>(result)});
        
        std::cout << "\n✓ Answer recorded. Future questions will minimize info leakage." << std::endl;
        std::cout << std::endl;
    }

    void GameManager::createAndAddConstraint(const uchar p1, const uchar p2, const OperationType op, const int result) {
        switch (op) {
            case OperationType::SUM:
                this->cspModel->addConstraint(std::make_unique<AdditiveConstraint>(this->variables[p1].get(), this->variables[p2].get(), static_cast<uchar>(result)));
                break;
            case OperationType::MUL:
                this->cspModel->addConstraint(std::make_unique<MultiplicativeConstraint>(this->variables[p1].get(), this->variables[p2].get(), static_cast<uchar>(result)));
                break;
            case OperationType::DIV:
                this->cspModel->addConstraint(std::make_unique<DivisionConstraint>(this->variables[p1].get(), this->variables[p2].get(), static_cast<uchar>(result)));
                break;
            case OperationType::ZEROCOUNT:
                this->cspModel->addConstraint(std::make_unique<ZeroConstraint>(this->variables[p1].get(), this->variables[p2].get(), static_cast<uchar>(result)));
                break;
            default:
                break;
        }
        this->roundCount++;
    }

    void GameManager::displayCurrentResults() {
        std::cout << "\n============================================" << std::endl;
        std::cout << "         CURRENT PARTIAL RESULTS" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "\nRound: " << this->roundCount << std::endl;
        std::cout << "\nCurrent state of knowledge:" << std::endl;
        
        for (size_t i = 0; i < this->variables.size(); ++i) {
            std::cout << "  Player " << static_cast<char>('A' + i) << ": ";
            
            const auto& domain = this->variables[i]->getDomain();
            
            if (domain.size() == 1) {
                std::cout << "FOUND = " << static_cast<int>(*domain.begin()) << std::endl;
            } else if (domain.size() <= 5) {
                std::cout << "Possible values: ";
                bool first = true;
                for (const auto& val : domain) {
                    if (!first) std::cout << ", ";
                    std::cout << static_cast<int>(val);
                    first = false;
                }
                std::cout << " (" << domain.size() << " possibilities)" << std::endl;
            } else {
                std::cout << domain.size() << " possible values remaining" << std::endl;
            }
        }
        
        std::cout << "\n============================================" << std::endl;
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

}