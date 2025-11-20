#include <iostream>
#include <vector>

#include "secretNumberDilemma/blackBox.h"
#include "secretNumberDilemma/gameManager.h"
#include "secretNumberDilemma/csp/cspModel.h"
#include "secretNumberDilemma/csp/variable.h"
#include "secretNumberDilemma/csp/cspModel.h"
#include "secretNumberDilemma/csp/constraint/additiveConstraint.h"

void displayWelcome() {
    std::cout << "============================================" << std::endl;
    std::cout << "   Secret Number Dilemma - CSP Solver" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::endl;
}

void displayGameRules() {
    std::cout << "\n=== Game Rules ===" << std::endl;
    std::cout << "Each player has a secret number between 1 and 100." << std::endl;
    std::cout << "All numbers are different." << std::endl;
    std::cout << "You can query the BlackBox with:" << std::endl;
    std::cout << "  + : Sum of two numbers (result between 2 and 200)" << std::endl;
    std::cout << "  * : Last digit of product (result between 0 and 9)" << std::endl;
    std::cout << "  % : Quotient max/min (result >= 1)" << std::endl;
    std::cout << "  0 : Number of 0s in the interval [min, max]" << std::endl;
    std::cout << "\nGoal: Determine all secret numbers!\n" << std::endl;
}

int main() {
    displayWelcome();
    
    // Game configuration
    int nbPlayers = 10;  // Default
    int myId = 0;        // Default
    bool useBlackBox = true;  // Default
    
    std::cout << "Number of players (3-10) [default: 10]: ";
    std::string input;
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        try {
            nbPlayers = std::stoi(input);
            if (nbPlayers < 3 || nbPlayers > 10) {
                std::cout << "Invalid number of players. Using 10 by default." << std::endl;
                nbPlayers = 10;
            }
        } catch (...) {
            std::cout << "Invalid input. Using 10 by default." << std::endl;
            nbPlayers = 10;
        }
    }
    
    std::cout << "Your ID (0-" << (nbPlayers-1) << ") [default: 0]: ";
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        try {
            myId = std::stoi(input);
            if (myId < 0 || myId >= nbPlayers) {
                std::cout << "Invalid ID. Using 0 by default." << std::endl;
                myId = 0;
            }
        } catch (...) {
            std::cout << "Invalid input. Using 0 by default." << std::endl;
            myId = 0;
        }
    }
    
    std::cout << "\nGame mode:" << std::endl;
    std::cout << "  1. With BlackBox (automatically generated numbers) [default]" << std::endl;
    std::cout << "  2. Manual mode (enter results yourself)" << std::endl;
    std::cout << "Choice [default: 1]: ";
    std::getline(std::cin, input);
    
    if (!input.empty()) {
        try {
            int mode = std::stoi(input);
            useBlackBox = (mode == 1);
        } catch (...) {
            std::cout << "Invalid input. Using BlackBox mode by default." << std::endl;
        }
    }
    
    if (useBlackBox) {
        displayGameRules();
        std::cout << "Press Enter to start...";
        std::cin.get();
    } else {
        std::cout << "\nManual mode activated." << std::endl;
        std::cout << "You will have to manually enter the results of operations." << std::endl;
        displayGameRules();
        std::cout << "Press Enter to start...";
        std::cin.get();
    }
    
    // Create game manager
    secretNumberDilemma::GameManager gm(
        static_cast<unsigned char>(nbPlayers), 
        static_cast<unsigned char>(myId), 
        useBlackBox
    );
    
    std::cout << "\n\n=== Game Start ===" << std::endl;
    std::cout << "You are player " << static_cast<char>('A' + myId) << std::endl;
    std::cout << "The system will suggest the best questions at each turn.\n" << std::endl;
    
    // Main game loop
    while (!gm.isGameOver()) {
        gm.update();
    }
    
    // Display question history
    gm.displayQuestionHistory();
    
    // Display final solution
    std::cout << "\n============================================" << std::endl;
    std::cout << "         PROBLEM SOLVED!" << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nFinal solution:" << std::endl;
    
    auto solution = gm.getSolution();
    for (auto i = 0; i < nbPlayers; ++i) {
        std::cout << "  " << static_cast<char>(65 + i) << " = " 
                  << static_cast<int>(solution[i]) << std::endl;
    }
    std::cout << "\n============================================" << std::endl;
    
    std::cout << "\nPress Enter to quit...";
    std::cin.get();

    return 0;
}



