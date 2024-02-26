#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

class BasketballPlayer {
public:
    std::string name;
    int shotsTaken;
    int shotsMade;
    int passesAttempted;
    int passesMade;

    BasketballPlayer(std::string playerName) {
        name = playerName;
        shotsTaken = 0;
        shotsMade = 0;
        passesAttempted = 0;
        passesMade = 0;
    }

    bool PassBall() {
        passesAttempted++;
        int passSuccessRate = (passesMade * 100) / (passesAttempted > 0 ? passesAttempted : 1);
        int randomNum = rand() % 100 + 1;
        if (randomNum > passSuccessRate + 50) {
            return false;
        }
        else {
            passesMade++;
            return true;
        }
    }

    int TakeShot(int points) {
        shotsTaken++;
        int shotSuccessRate = (shotsMade * 100) / (shotsTaken > 0 ? shotsTaken : 1);
        int randomNum;
        if (points == 1) {
            randomNum = rand() % 70 + 1;
        }
        else if (points == 2) {
            randomNum = rand() % 100 + 1;
        }
        else { // assuming 3-point shot
            randomNum = rand() % 125 + 1;
        }

        if (randomNum < shotSuccessRate + 50) {
            shotsMade++;
            return points;
        }
        else {
            return 0;
        }
    }
};

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));  // Initialize random number generator

    // Initialize players
    std::vector<BasketballPlayer> players = {
        BasketballPlayer("Player 1"),
        BasketballPlayer("Player 2"),
        BasketballPlayer("Player 3"),
        BasketballPlayer("Player 4"),
        BasketballPlayer("Player 5")
    };

    int userScore = 0;
    int opponentScore = 0;
    int possessions = 30;

    for (int i = 0; i < possessions; ++i) {
        // User's turn
        int currentPlayerIndex = rand() % players.size();
        BasketballPlayer& currentPlayer = players[currentPlayerIndex];

        std::cout << "Current player: " << currentPlayer.name << std::endl;
        std::cout << "Choose action: 1. Shoot  2. Pass  3. Check Stats  4. Check Score" << std::endl;
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: { // Shoot
            std::cout << "Choose shot value (1, 2, or 3): ";
            int shotValue;
            std::cin >> shotValue;
            userScore += currentPlayer.TakeShot(shotValue);
            break;
        }
        case 2: { // Pass
            if (!currentPlayer.PassBall()) {
                std::cout << "Pass failed! Turnover.\n";
                i--; // Extra possession for opponent
            }
            break;
        }
        case 3: { // Check Stats
            for (const auto& player : players) {
                std::cout << "Player: " << player.name
                    << ", Shots Made: " << player.shotsMade
                    << ", Shots Taken: " << player.shotsTaken
                    << ", Passes Made: " << player.passesMade
                    << ", Passes Attempted: " << player.passesAttempted << std::endl;
            }
            break;
        }
        case 4: { // Check Score
            std::cout << "Current Score: User - " << userScore << ", Opponent - " << opponentScore << std::endl;
            break;
        }
        default:
            std::cout << "Invalid choice. Please try again.\n";
            i--;
            continue;
        }

        // Opponent's turn logic
        bool opponentPossession = true;
        while (opponentPossession) {
            if (rand() % 100 < 60) { // 60% chance to make a 2-point shot
                opponentScore += 2;
                opponentPossession = false;
            }
            else if (rand() % 100 >= 50) { // 50% chance to retain possession after missing
                opponentPossession = true;
            }
            else {
                opponentPossession = false;
            }
        }
    }

    std::cout << "Final Score: User - " << userScore << ", Opponent - " << opponentScore << std::endl;
    return 0;
}

